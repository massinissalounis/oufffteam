#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM3IF)
/*************************************************************************
* Function Name     : SetHSSecPWMDutyCycle3
* Description       : Provides the duty cycle value for the PWM3L output if independent 
*					  time base is selected                      
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMSecDutyCycle3(unsigned int dutycycle )
{
    SDC3 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
