#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : SetHSSecPWMDutyCycle1
* Description       : Provides the duty cycle value for the PWM1L output if independent 
*					  time base is selected                      
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMSecDutyCycle1(unsigned int dutycycle )
{
    SDC1 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
