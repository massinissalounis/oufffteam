#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include "p24Hxxxx.h"
#endif

#include "rtcc.h"

#ifdef _TMR_RTCC_V1

/*********************************************************************
 * Function:        void RtccWriteTimeDate(const rtccTimeDate* pTD)
 *
 * PreCondition:    rtccTimeDate structure fields have to have proper values:
 *                      - sec:  BCD codification, 00-59 
 *                      - min:  BCD codification, 00-59
 *                      - hour: BCD codification, 00-24
 *                      - wday: BCD codification, 00-06 
 *                      - mday: BCD codification, 01-31
 *                      - mon: BCD codification, 01-12
 *                      - year: BCD codification, 00-99
 * Input:           pTD - pointer to a rtccTimeDate union to store the current 
 *                        time and date
 *                  di  - if interrupts need to be disabled
 * Output:          TRUE '1' : If all the values are within range
 *                  FALSE '0' : If any value is out of above mentioned range.
 * Side Effects:    None
 * Overview:        The function sets the current time and date of the RTCC device.
 * Note:            - The write is successful only if Wr Enable is set.
 *                  The function will enable the write itself, if needed.
 *                  Also, the Alarm will be temporarily disabled and the
 *                  device will be stopped (On set to 0) in order
 *                  to safely perform the update of the RTC time register.
 *                  However, the device status will be restored.
 *                  - Usually the disabling of the interrupts is desired, if the user has to have more
 *                  precise control over the actual moment of the time setting.
 ********************************************************************/
BOOL RtccWriteTimeDate(const rtccTimeDate* pTD , BOOL di)
{
   BOOL        wasWrEn;
   BOOL        wasOn;
   BOOL        wasAlrm=FALSE;
   UINT8  CPU_IPL;

   if((MAX_MIN < pTD->b[7]) || (MAX_SEC < pTD->b[6]) || (MAX_WDAY < pTD->b[5]) || (MAX_HOUR < pTD->b[4]) || 
      (MAX_MON < pTD->b[3]) || (MIN_MON > pTD->b[3]) || (MAX_MDAY < pTD->b[2]) || (MIN_MDAY > pTD->b[2]) || 
      (MAX_YEAR < pTD->b[0]))
   {
       return(FALSE);
   }

   if(di)
   {
      /* Disable Global Interrupt */
      mSET_AND_SAVE_CPU_IP(CPU_IPL,7);
   }
   
   if(!(wasWrEn= mRtccIsWrEn()))
   {
       RtccWrOn();            // have to allow the WRTEN in order to write the new value
   }
   if((wasOn= mRtccIsOn()))
   {
       wasAlrm= mRtccIsAlrmEnabled();
       mRtccOff();         // turn module off before updating the time
   }


   mRtccClearRtcPtr();
   mRtccSetRtcPtr(RTCCPTR_MASK_YEAR);

   mRtccWaitSync();     // wait until device signals read/write is safe.

   RTCVAL=pTD->w[0];
   RTCVAL=pTD->w[1];
   RTCVAL=pTD->w[2];
   RTCVAL=pTD->w[3];   // update the RTCTIME value

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
