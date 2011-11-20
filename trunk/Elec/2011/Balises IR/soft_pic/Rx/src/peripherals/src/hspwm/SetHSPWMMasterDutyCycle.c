#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : SetHSPWMMasterDutyCycle
* Description       : This function Provides the Master duty cycle value for the 
*					  PWM Module
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetHSPWMMasterDutyCycle(unsigned int dutycycle )
{
    MDC = dutycycle;
}
#else
#warning "Does not build on this target"
#endif
 
