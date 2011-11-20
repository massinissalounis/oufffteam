#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM2IF)
/*************************************************************************
* Function Name     : SetHSPWMDutyCycle2
* Description       : This function Provides the duty cycle value for the 
*					  PWM2H output or PWM2H and PWM2L outputs if shared time base is selected
*					  Provides the duty cycle value for the PWM2H output if independent 
*					  time base is selected                       
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMDutyCycle2(unsigned int dutycycle )
{
    PDC2 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
