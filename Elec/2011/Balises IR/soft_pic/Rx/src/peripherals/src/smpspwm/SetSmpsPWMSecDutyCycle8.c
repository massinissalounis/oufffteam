#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#if defined(__dsPIC33F__)

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM8IF 


/*************************************************************************
* Function Name     : SetSmpsSecPWMDutyCycle8
* Description       : Provides the duty cycle value for the PWM8L output if independent 
*					  time base is selected                      
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMSecDutyCycle8(unsigned int dutycycle )
{
    SDC8 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
#endif 

#endif
