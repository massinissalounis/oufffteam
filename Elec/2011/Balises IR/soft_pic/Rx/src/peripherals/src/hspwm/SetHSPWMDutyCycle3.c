#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM3IF)
/*************************************************************************
* Function Name     : SetHSPWMDutyCycle3
* Description       : This function Provides the duty cycle value for the 
*					  PWM3H output or PWM3H and PWM3L outputs if shared time base is selected
*					  Provides the duty cycle value for the PWM3H output if independent 
*					  time base is selected                       
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMDutyCycle3(unsigned int dutycycle )
{
    PDC3 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
