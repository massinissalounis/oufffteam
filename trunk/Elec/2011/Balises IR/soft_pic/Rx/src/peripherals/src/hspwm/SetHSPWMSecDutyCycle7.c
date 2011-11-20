#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM7IF)
/*************************************************************************
* Function Name     : SetHSSecPWMDutyCycle7
* Description       : Provides the duty cycle value for the PWM7L output if independent 
*					  time base is selected                      
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMSecDutyCycle7(unsigned int dutycycle )
{
    SDC7 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
