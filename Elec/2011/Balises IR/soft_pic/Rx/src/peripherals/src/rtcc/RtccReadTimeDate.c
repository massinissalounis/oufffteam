#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include "p24Hxxxx.h"
#endif

#include "rtcc.h"

#ifdef _TMR_RTCC_V1

/*********************************************************************
 * Function:        void RtccReadTimeDate(rtccTimeDate* pTD)
 *
 * PreCondition:    None
 * Input:           pTD - pointer to a rtccTimeDate union to store the current 
 *                        time and date
 * Output:          None
 * Side Effects:    None
 * Overview:        The function updates the user supplied union/structure with
 *                  the current time and date of the RTCC device.
 * Note:            This firmware solution would consist of reading each       
 *                  register twice and then comparing the two values. If the   
 *                  two values match, then a rollover did not occur.
 ********************************************************************/
void RtccReadTimeDate(rtccTimeDate* pTD)
{
   rtccTimeDate	currTD;
   do
   {
      mRtccClearRtcPtr();
      mRtccSetRtcPtr(RTCCPTR_MASK_YEAR);

      pTD->w[0]=RTCVAL;
      pTD->w[1]=RTCVAL;
      pTD->w[2]=RTCVAL;
      pTD->w[3]=RTCVAL;    // read the device value
   
      mRtccClearRtcPtr();
      mRtccSetRtcPtr(RTCCPTR_MASK_YEAR);
   
      currTD.w[0]=RTCVAL;
      currTD.w[1]=RTCVAL;
      currTD.w[2]=RTCVAL;
      currTD.w[3]=RTCVAL;    // read the device value

   }while(pTD->f.sec!=currTD.f.sec);	// make sure you have the same sec
}


#else
#warning "Does not build on this target"
#endif
