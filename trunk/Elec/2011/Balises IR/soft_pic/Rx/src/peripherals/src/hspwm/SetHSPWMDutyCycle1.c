#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : SetHSPWMDutyCycle1
* Description       : This function Provides the duty cycle value for the 
*					  PWM1H output or PWM1H and PWM1L outputs if shared time base is selected
*					  Provides the duty cycle value for the PWM1H output if independent 
*					  time base is selected                       
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMDutyCycle1(unsigned int dutycycle )
{
    PDC1 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
