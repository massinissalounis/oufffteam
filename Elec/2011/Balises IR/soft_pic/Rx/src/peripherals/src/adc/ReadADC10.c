#include "adc10.h"

#ifdef _ADC_10BIT

/************************************************************************
* Function Name     : ReadADC10
* Description       : This function reads from one of the 16 ADC Buffers
                      (ADCBUF0 - ADCBUFF)
* Parameters        : unsigned char bufIndex
* Return Value      : unsigned int
*************************************************************************/

unsigned int ReadADC10(unsigned char bufIndex)
{
     return(*(&ADCBUF0+bufIndex));
}

#else
#warning "Does not build on this target"
#endif

