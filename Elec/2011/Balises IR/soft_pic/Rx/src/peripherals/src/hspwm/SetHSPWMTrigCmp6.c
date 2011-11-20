#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM6IF)
/*************************************************************************
* Function Name     : SetHSPWMTrigCmp6
* Description       : This function configures the Trigger compare value  for generating trigger to the 
*                     ADC module for initiating a sample and conversion process or generating 
*                     trigger interrupt to PWM6 output pair
* Parameters        : unsigned int trigcmp_val
* Return Value      : None 
**************************************************************************/

void SetHSPWMTrigCmp6(unsigned int trigcmp_val )
{
    TRIG6 = trigcmp_val ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
