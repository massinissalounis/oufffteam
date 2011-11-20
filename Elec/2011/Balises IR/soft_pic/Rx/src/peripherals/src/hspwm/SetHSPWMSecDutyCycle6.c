#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM6IF)
/*************************************************************************
* Function Name     : SetHSSecPWMDutyCycle6
* Description       : Provides the duty cycle value for the PWM6L output if independent 
*					  time base is selected                      
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMSecDutyCycle6(unsigned int dutycycle )
{
    SDC6 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
