#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM6IF)
/*************************************************************************
* Function Name     : SetHSPWMDutyCycle6
* Description       : This function Provides the duty cycle value for the 
*					  PWM6H output or PWM6H and PWM6L outputs if shared time base is selected
*					  Provides the duty cycle value for the PWM6H output if independent 
*					  time base is selected                       
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMDutyCycle6(unsigned int dutycycle )
{
    PDC6 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
