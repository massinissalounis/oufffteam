#include <adc.h>

#ifdef _AD2IF

/*********************************************************************
* Function Name     : SetChanADC2
* Description       : This function sets the AD1CHS123 and AD1CHS0 reg to 
*                     get the +ve and -ve of sample inputs A and B.
* Parameters        : unsigned int channel123, unsigned int channel0
* Return Value      : None
*********************************************************************/

void SetChanADC2(unsigned int channel123,unsigned int channel0)
{
    AD2CHS123 = channel123;
    AD2CHS0 = channel0;
}

#else
#warning "Does not build on this target"
#endif
