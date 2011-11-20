#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM4IF)
/*************************************************************************
* Function Name     : SetHSSecPWMDutyCycle4
* Description       : Provides the duty cycle value for the PWM4L output if independent 
*					  time base is selected                      
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMSecDutyCycle4(unsigned int dutycycle )
{
    SDC4 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
