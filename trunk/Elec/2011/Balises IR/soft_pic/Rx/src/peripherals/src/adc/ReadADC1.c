#include <adc.h>

#ifdef _AD1IF

/************************************************************************
* Function Name     : ReadADC1
* Description       : This function reads from one of the 16 ADC Buffers
                      (ADCBUF0 - ADCBUFF)
* Parameters        : unsigned char bufIndex
* Return Value      : unsigned int
*************************************************************************/

unsigned int ReadADC1(unsigned char bufIndex)
{
     return(*(&ADC1BUF0+bufIndex));
}

#else
#warning "Does not build on this target"
#endif

