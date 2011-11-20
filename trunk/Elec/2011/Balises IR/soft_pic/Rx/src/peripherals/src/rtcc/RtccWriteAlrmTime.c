#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include "p24Hxxxx.h"
#endif

#include "rtcc.h"

#ifdef _TMR_RTCC_V1

/*********************************************************************
 * Function:        void RtccWriteAlrmTime(const rtccTime* pTm)
 *
 * PreCondition:    pTm a valid rtccTime pointer having proper values:
 *                      - sec:  BCD codification, 00-59 
 *                      - min:  BCD codification, 00-59
 *                      - hour: BCD codification, 00-24
 * Input:           pTm - pointer to a constant rtccTime union
 * Output:          None
 * Side Effects:    None
 * Overview:        The function sets the current alarm time in the RTCC device.
 * Note:            - The write is successful only if Wr Enable is set.
 *                  The function will enable the write itself, if needed.
 *                  Also, the Alarm will be temporarily disabled in order
 *                  to safely perform the update of the ALRMTIME register.
 *                  However, the device status will be restored.
 ********************************************************************/
BOOL RtccWriteAlrmTime(const rtccTime* pTm)
{
   WORD_VAL tempHourWDay ;
   WORD_VAL tempMinSec ;

   BOOL    wasWrEn;
   BOOL    wasAlrm;

   if((MAX_MIN < pTm->f.min)|| (MAX_SEC < pTm->f.sec) || (MAX_HOUR < pTm->f.hour))
   {
       return FALSE;
   }

   tempMinSec.byte.HB = pTm->f.min;
   tempMinSec.byte.LB =pTm->f.sec;        // update the desired fields

   if(!(wasWrEn=mRtccIsWrEn()))
   {
       RtccWrOn();            // have to allow the WRTEN in order to write the new value
   }
   if((wasAlrm=mRtccIsAlrmEnabled()))
   {
       mRtccAlrmDisable();     // avoid spurious alarm interrupts
   }

   mRtccClearAlrmPtr();
   mRtccSetAlrmPtr(RTCCPTR_MASK_HRSWEEK);

   tempHourWDay.Val = ALRMVAL;
   tempHourWDay.byte.LB = pTm->f.hour;

   mRtccClearRtcPtr();
   mRtccSetRtcPtr(RTCCPTR_MASK_HRSWEEK);

   ALRMVAL = tempHourWDay.Val;
   ALRMVAL = tempMinSec.Val;

   if(wasAlrm)
   {
       mRtccAlrmEnable();
   }
   if(!wasWrEn)
   {
       mRtccWrOff();
   }

   return(TRUE);
}


#else
#warning "Does not build on this target"
#endif
