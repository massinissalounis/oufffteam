#include <adc.h>

#ifdef _AD2IF

/***********************************************************************
* Function Name     : ReadADC2
* Description       : This function reads from one of the 16 ADC Buffers
                      (ADCBUF0 - ADCBUFF)
* Parameters        : unsigned char bufIndex
* Return Value      : unsigned int
************************************************************************/

unsigned int ReadADC2(unsigned char bufIndex)
{
     return(*(&ADC2BUF0+bufIndex));
}

#else
#warning "Does not build on this target"
#endif
