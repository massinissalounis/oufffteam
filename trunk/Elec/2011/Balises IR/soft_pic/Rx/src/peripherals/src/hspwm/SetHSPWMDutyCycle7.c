#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM7IF)
/*************************************************************************
* Function Name     : SetHSPWMDutyCycle7
* Description       : This function Provides the duty cycle value for the 
*					  PWM7H output or PWM7H and PWM7L outputs if shared time base is selected
*					  Provides the duty cycle value for the PWM7H output if independent 
*					  time base is selected                       
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMDutyCycle7(unsigned int dutycycle )
{
    PDC7 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
