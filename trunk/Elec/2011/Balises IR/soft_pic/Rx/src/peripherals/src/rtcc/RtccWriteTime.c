#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include "p24Hxxxx.h"
#endif

#include "rtcc.h"

#ifdef _TMR_RTCC_V1

/*********************************************************************
 * Function:        BOOL RtccWriteTime(const rtccTime* pTm, BOOL di)
 *
 * PreCondition:    pTm pointing to a valid rtccTime structure having proper values:
 *                      - sec:  BCD codification, 00-59 
 *                      - min:  BCD codification, 00-59
 *                      - hour: BCD codification, 00-24
 * Input:           pTm - pointer to a constant rtccTime union
 *                  di  - if interrupts need to be disabled
 * Output:          TRUE '1' : If all the values are within range
 *                  FALSE '0' : If any value is out of above mentioned range.
 * Side Effects:    None
 * Overview:        The function sets the current time of the RTCC device.
 * Note:            - The write is successful only if Wr Enable is set.
 *                  The function will enable the write itself, if needed.
 *                  Also, the Alarm will be temporarily disabled and the
 *                  device will be stopped (On set to 0) in order
 *                  to safely perform the update of the RTC time register.
 *                  However, the device status will be restored.
 *                  - Usually the disabling of the interrupts is desired, if the user has to have more
 *                  precise control over the actual moment of the time setting.
 ********************************************************************/
BOOL RtccWriteTime(const rtccTime* pTm , BOOL di)
{
   WORD_VAL tempHourWDay ;
   WORD_VAL tempMinSec ;
   UINT8  CPU_IPL;

   BOOL        wasWrEn;
   BOOL        wasOn;
   BOOL        wasAlrm=FALSE;

   if((MAX_MIN < pTm->f.min )|| (MAX_SEC < pTm->f.sec) || (MAX_HOUR < pTm->f.hour))
   {
       return(FALSE);
   }

   tempMinSec.byte.HB = pTm->f.min;
   tempMinSec.byte.LB =pTm->f.sec;        // update the desired fields

   if(di)
   {
      /* Disable Global Interrupt */
      mSET_AND_SAVE_CPU_IP(CPU_IPL,7);
   }
   
   if(!(wasWrEn= mRtccIsWrEn()))
   {
       RtccWrOn();            // have to allow the WRTEN in order to write the new value
   }
   if((wasOn=mRtccIsOn()))
   {
       wasAlrm= mRtccIsAlrmEnabled();
       mRtccOff();         // turn module off before updating the time
   }

   mRtccClearRtcPtr();
   mRtccSetRtcPtr(RTCCPTR_MASK_HRSWEEK);

   tempHourWDay.Val = RTCVAL;
   tempHourWDay.byte.LB = pTm->f.hour;


   mRtccClearRtcPtr();
   mRtccSetRtcPtr(RTCCPTR_MASK_HRSWEEK);

   RTCVAL = tempHourWDay.Val; // update device value
   RTCVAL = tempMinSec.Val;

   if(wasOn)
   {
       mRtccOn();
       if(wasAlrm)
       {
           mRtccAlrmEnable();
       }
   
       if(wasWrEn)
       {
           RtccWrOn();
       }
   }
   else
   {
       if(!wasWrEn)
       {
           mRtccWrOff();
       }
   }
   
   if(di)
   {
      /* Enable Global Interrupt */
      mRESTORE_CPU_IP(CPU_IPL);
   }
   

   return(TRUE);
}


#else
#warning "Does not build on this target"
#endif
