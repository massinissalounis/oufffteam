#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM5IF)
/*************************************************************************
* Function Name     : SetHSSecPWMDutyCycle5
* Description       : Provides the duty cycle value for the PWM5L output if independent 
*					  time base is selected                      
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMSecDutyCycle5(unsigned int dutycycle )
{
    SDC5 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
