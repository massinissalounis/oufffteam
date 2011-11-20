#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include "p24Hxxxx.h"
#endif

#include "rtcc.h"

#ifdef _TMR_RTCC_V1

/*********************************************************************
 * Function:        void RtccSetCalibration(int drift)
 *
 * PreCondition:    drift has to fit into signed 8 bits representation 
 * Input:           drift   - value to be added/subtracted to perform calibration 
 * Output:          None
 * Side Effects:    None
 * Overview:        The function updates the value that the RTCC uses in the
 *                  auto-adjust feature, once every minute.
 *                  The drift value acts as a signed value, [-128*4, +127*4], 0 not having
 *                  any effect.
 * Note:            - Writes to the RCFGCAL.CAL[7:0] register should  only occur when the timer
 *                  is turned off or immediately or after the edge of the seconds pulse
 *                  (except when SECONDS=00 - due to the possibility of the auto-adjust event).
 *                  In order to speed-up the process, the API function performs the reading
 *                  of the HALFSEC field.
 *                  - The function may block for half a second, worst case, when called
 *                  at the start of the minute.
 *                  - Interrupts can not be disabled for such a long period. However, long interrupt routines
 *                  can interfere with the proper functioning of the device. Care must be taken.
 ********************************************************************/
void RtccSetCalibration(int drift)
{
   if(mRtccIsOn())
   {
       UINT16  currSec;

       mRtccClearRtcPtr();     // make sure you read seconds

       if((currSec=RTCVAL)&(0xff==00))
       {   // we're at second 00, wait auto-adjust to be performed

           while(!mRtccIs2ndHalfSecond()); // wait until second half...
       }
   }
   
   // update the CAL value
   RCFGCALbits.CAL=drift;
}

#else
#warning "Does not build on this target"
#endif
