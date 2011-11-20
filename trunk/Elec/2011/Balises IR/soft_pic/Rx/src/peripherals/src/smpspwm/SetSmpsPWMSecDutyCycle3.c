#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#if defined(__dsPIC33F__)

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM3IF 


/*************************************************************************
* Function Name     : SetSmpsSecPWMDutyCycle3
* Description       : Provides the duty cycle value for the PWM3L output if independent 
*					  time base is selected                      
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMSecDutyCycle3(unsigned int dutycycle )
{
    SDC3 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
#endif 

#endif
