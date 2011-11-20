#include <adc.h>

#ifdef _AD1IF

/*********************************************************************
* Function Name     : SetChanADC10
* Description       : This function sets the AD1CHS123 and AD1CHS0 reg to 
*                     get the +ve and -ve of sample inputs A and B.
* Parameters        : unsigned int channel123, unsigned int channel0
* Return Value      : None
*********************************************************************/

void SetChanADC1(unsigned int channel123, unsigned int channel0)
{
    AD1CHS123 = channel123;
    AD1CHS0 = channel0;
}

#else
#warning "Does not build on this target"
#endif
