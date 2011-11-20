#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include "p24Hxxxx.h"
#endif

#include "rtcc.h"

#ifdef _TMR_RTCC_V1

/*********************************************************************
 * Function:        void RtccReadTime(rtccTime* pTm)
 *
 * PreCondition:    pTm a valid pointer
 * Input:           pTm - pointer to a rtccTime union to store the current time
 * Output:          None
 * Side Effects:    None
 * Overview:        The function updates the user supplied union/structure with
 *                  the current time of the RTCC device.
 * Note:            The function makes sure that the read value is valid.
 *                  It avoids waiting for the RTCSYNC to be clear by 
 *                  performing successive reads.
 ********************************************************************/
void RtccReadTime(rtccTime* pTm)
{
   rtccTimeDate rTD0, rTD1;

   do
   {
      mRtccClearRtcPtr();
      mRtccSetRtcPtr(RTCCPTR_MASK_HRSWEEK);

      rTD0.w[2]=RTCVAL;
      rTD0.w[3]=RTCVAL;    // read the device value
   
      mRtccClearRtcPtr();
      mRtccSetRtcPtr(RTCCPTR_MASK_HRSWEEK);
   
      rTD1.w[2]=RTCVAL;
      rTD1.w[3]=RTCVAL;    // read the device value

   }while(rTD0.f.sec!=rTD1.f.sec); // make sure you have the same sec

   pTm->f.hour=rTD0.f.hour;
   pTm->f.min=rTD0.f.min;
   pTm->f.sec=rTD0.f.sec;    // update user's data

}


#else
#warning "Does not build on this target"
#endif
