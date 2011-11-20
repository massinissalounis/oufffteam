#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#if defined(__dsPIC33F__)

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM2IF 


/*************************************************************************
* Function Name     : SetSmpsSecPWMDutyCycle2
* Description       : Provides the duty cycle value for the PWM2L output if independent 
*					  time base is selected                      
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMSecDutyCycle2(unsigned int dutycycle )
{
    SDC2 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
#endif 

#endif
