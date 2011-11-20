#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM2IF 


/*************************************************************************
* Function Name     : SetSmpsPWMDutyCycle2
* Description       : This function Provides the duty cycle value for the 
*					  PWM2H output or PWM2H and PWM2L outputs if shared time base is selected
*					  if defined(__dsPIC33F__)					  
*					  Provides the duty cycle value for the PWM2H output if independent 
*					  time base is selected                       
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/


void SetSmpsPWMDutyCycle2(unsigned int dutycycle )
{
    PDC2 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
#endif 
