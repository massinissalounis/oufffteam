

#include "rtcc.h"
#ifdef _TMR_RTCC_V1

/*********************************************************************
 * Function:        void RtccReadAlrmDate(rtccDate* pDt)
 *
 * PreCondition:    pDt a valid pointer
 * Input:           pDt - pointer to a rtccDate union to store the alarm Date
 * Output:          None
 * Side Effects:    None
 * Overview:        The function updates the user supplied union/structure with
 *                  the current alarm Date of the RTCC device.
 ********************************************************************/


void RtccReadAlrmDate(rtccDate* pDt)
{
   rtccTimeDate rTD;

   mRtccClearAlrmPtr();
  mRtccSetAlrmPtr( RTCCPTR_MASK_DAYMON);

   rTD.w[1]=ALRMVAL;
   rTD.w[2]=ALRMVAL;

   pDt->f.mday = rTD.f.mday;
   pDt->f.mon = rTD.f.mon;
   pDt->f.wday = rTD.f.wday;    // update user's data
}


#else
#warning "Does not build on this target"
#endif
