#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include "p24Hxxxx.h"
#endif

#include "rtcc.h"

#ifdef _TMR_RTCC_V1

/*********************************************************************
 * Function:        void _RtccWrOn(void)
 *
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        Function to set the RCFGCAL.RTCWREN.
 * Note:            The interrupts are disabled in order to have a proper device initialization
 ********************************************************************/
void RtccWrOn(void)
{
   UINT8  CPU_IPL;
   unsigned int data;

/* Disable Global Interrupt */
   mSET_AND_SAVE_CPU_IP(CPU_IPL,7);

   asm volatile ("MOV #0x55,%0" : "=r"(data));
   asm volatile ("MOV %0,NVMKEY" : : "r"(data)); // Write the 0x55 key
   asm volatile ("MOV #0xAA,%0" : "=r"(data));
   asm volatile ("MOV %0,NVMKEY"  : : "r"(data)); // Write the 0xAA key

   RCFGCALbits.RTCWREN=1;  

/* Enable Global Interrupt */
   mRESTORE_CPU_IP(CPU_IPL);
}


#else
#warning "Does not build on this target"
#endif
