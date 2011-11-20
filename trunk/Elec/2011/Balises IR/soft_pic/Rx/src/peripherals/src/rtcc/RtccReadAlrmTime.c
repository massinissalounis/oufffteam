#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include "p24Hxxxx.h"
#endif

#include "rtcc.h"

#ifdef _TMR_RTCC_V1

/*********************************************************************
 * Function:        void RtccReadAlrmTime(rtccTime* pTm)
 *
 * PreCondition:    pTm a valid pointer
 * Input:           pTm - pointer to a rtccTime union to store the alarm time
 * Output:          None
 * Side Effects:    None
 * Overview:        The function updates the user supplied union/structure with
 *                  the current alarm time of the RTCC device.
 ********************************************************************/
void RtccReadAlrmTime(rtccTime* pTm)
{
   rtccTimeDate rTD;

   mRtccClearAlrmPtr();
   mRtccSetAlrmPtr(RTCCPTR_MASK_HRSWEEK);

   rTD.w[2]=ALRMVAL;
   rTD.w[3]=ALRMVAL;  // read the device value

   pTm->f.hour=rTD.f.hour;
   pTm->f.min=rTD.f.min;
   pTm->f.sec=rTD.f.sec;    // update user's data
}


#else
#warning "Does not build on this target"
#endif
