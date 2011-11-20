#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM5IF)
/*************************************************************************
* Function Name     : SetHSPWMDutyCycle5
* Description       : This function Provides the duty cycle value for the 
*					  PWM5H output or PWM5H and PWM5L outputs if shared time base is selected
*					  Provides the duty cycle value for the PWM5H output if independent 
*					  time base is selected                       
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMDutyCycle5(unsigned int dutycycle )
{
    PDC5 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
