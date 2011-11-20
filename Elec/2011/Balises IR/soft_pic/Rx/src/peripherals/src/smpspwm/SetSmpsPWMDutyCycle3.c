#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM3IF 


/*************************************************************************
* Function Name     : SetSmpsPWMDutyCycle3
* Description       : This function Provides the duty cycle value for the 
*					  PWM3H output or PWM3H and PWM3L outputs if shared time base is selected
*					  if defined(__dsPIC33F__)					  
*					  Provides the duty cycle value for the PWM3H output if independent 
*					  time base is selected                       
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMDutyCycle3(unsigned int dutycycle )
{
    PDC3 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
#endif 
