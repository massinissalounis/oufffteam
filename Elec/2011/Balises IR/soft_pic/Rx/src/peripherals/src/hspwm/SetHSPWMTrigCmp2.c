#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM2IF)
/*************************************************************************
* Function Name     : SetHSPWMTrigCmp2
* Description       : This function configures the Trigger compare value  for generating trigger to the 
*                     ADC module for initiating a sample and conversion process or generating 
*                     trigger interrupt to PWM2 output pair
* Parameters        : unsigned int trigcmp_val
* Return Value      : None 
**************************************************************************/

void SetHSPWMTrigCmp2(unsigned int trigcmp_val )
{
    TRIG2 = trigcmp_val ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
