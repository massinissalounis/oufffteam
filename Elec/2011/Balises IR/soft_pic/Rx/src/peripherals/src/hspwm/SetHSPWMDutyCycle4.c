#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM4IF)
/*************************************************************************
* Function Name     : SetHSPWMDutyCycle4
* Description       : This function Provides the duty cycle value for the 
*					  PWM4H output or PWM4H and PWM4L outputs if shared time base is selected
*					  Provides the duty cycle value for the PWM4H output if independent 
*					  time base is selected                       
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMDutyCycle4(unsigned int dutycycle )
{
    PDC4 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
