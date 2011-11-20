#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM2IF)
/*************************************************************************
* Function Name     : SetHSSecPWMDutyCycle2
* Description       : Provides the duty cycle value for the PWM2L output if independent 
*					  time base is selected                      
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMSecDutyCycle2(unsigned int dutycycle )
{
    SDC2 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
