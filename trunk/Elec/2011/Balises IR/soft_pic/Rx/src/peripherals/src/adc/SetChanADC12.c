#include "adc12.h"

#ifdef _ADC_12BIT

/*********************************************************************
* Function Name     : SetChanADC12
* Description       : This function sets the ADCHS reg to get the +ve 
*                     and -ve of sample inputs A and B.
* Parameters        : unsigned int channel
* Return Value      : None
*********************************************************************/

void SetChanADC12(unsigned int channel)
{
    ADCHS = channel;
}

#else
#warning "Does not build on this target"
#endif
