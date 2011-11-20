#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include "p24Hxxxx.h"
#endif

#include "rtcc.h"

#ifdef _TMR_RTCC_V1

/*********************************************************************
 * Function:        void RtccReadDate(rtccDate* pDt)
 *
 * PreCondition:    pDt a valid pointer
 * Input:           pDt - pointer to a rtccTime union to store the current time
 * Output:          None
 * Side Effects:    None
 * Overview:        The function updates the user supplied union/structure with
 *                  the current time of the RTCC device.
 * Note:            - The function makes sure that the read value is valid.
 *                  It avoids waiting for the RTCSYNC to be clear by 
 *                  performing successive reads.
 ********************************************************************/
void RtccReadDate(rtccDate* pDt)
{
   rtccTimeDate rTD0, rTD1;
   do
   {
      mRtccClearRtcPtr();
      mRtccSetRtcPtr(RTCCPTR_MASK_YEAR);

      rTD0.w[0]=RTCVAL;
      rTD0.w[1]=RTCVAL;
      rTD0.w[2]=RTCVAL;
   
      mRtccClearRtcPtr();
      mRtccSetRtcPtr(RTCCPTR_MASK_YEAR);

      rTD1.w[0]=RTCVAL;
      rTD1.w[1]=RTCVAL;
      rTD1.w[2]=RTCVAL;

   }while(rTD0.f.mday!=rTD1.f.mday); // make sure you have the same month day

   pDt->f.mday=rTD0.f.mday; // update user's union
   pDt->f.mon=rTD0.f.mon;
   pDt->f.wday=rTD0.f.wday;
   pDt->f.year=rTD0.f.year;
}


#else
#warning "Does not build on this target"
#endif
