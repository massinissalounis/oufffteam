#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include "p24Hxxxx.h"
#endif

#include "rtcc.h"

#ifdef _TMR_RTCC_V1

/*********************************************************************
 * Function:        void RtccReadAlrmTimeDate(rtccTimeDate* pTD)
 *
 * PreCondition:    None
 * Input:           pTD - pointer to a rtccTimeDate union to store the alarm time and date
 * Output:          None
 * Side Effects:    None
 * Overview:        The function updates the user supplied union/structure with
 *                  the current alarm time and date of the RTCC device.
 * Note:            None
 ********************************************************************/
void RtccReadAlrmTimeDate(rtccTimeDate* pTD)
{
   mRtccClearAlrmPtr();
   mRtccSetAlrmPtr(RTCCPTR_MASK_DAYMON);

   pTD->w[1]=ALRMVAL;
   pTD->w[2]=ALRMVAL;
   pTD->w[3]=ALRMVAL;  // updates the user value
}


#else
#warning "Does not build on this target"
#endif
