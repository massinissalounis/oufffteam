#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include "p24Hxxxx.h"
#endif

#include "rtcc.h"

#ifdef _TMR_RTCC_V1


/*********************************************************************
 * Function:        void RtccInitClock(void)
 *
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        The function initializes the RTCC device. It starts the RTCC clock,
 *                  sets the RTCC Off and disables RTCC write. Disables the OE.
 * Note:            None
 ********************************************************************/
void RtccInitClock(void)
{
   // enable the Secondary Oscillator
   __builtin_write_OSCCONL(2);

   RCFGCAL = 0x0;
   if(mRtccIsOn())
   {
      if(!mRtccIsWrEn())
      {
          RtccWrOn();
      }
       mRtccOff();
   }
   
   mRtccWrOff();
}

#else
#warning "Does not build on this target"
#endif
