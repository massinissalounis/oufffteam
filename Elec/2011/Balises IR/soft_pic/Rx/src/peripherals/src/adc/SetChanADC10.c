#include "adc10.h"

#ifdef _ADC_10BIT

/*********************************************************************
* Function Name     : SetChanADC10
* Description       : This function sets the ADCHS reg to get the +ve 
*                     and -ve of sample inputs A and B.
* Parameters        : unsigned int channel
* Return Value      : None
*********************************************************************/

void SetChanADC10(unsigned int channel)
{
    ADCHS = channel;
}

#else
#warning "Does not build on this target"
#endif

