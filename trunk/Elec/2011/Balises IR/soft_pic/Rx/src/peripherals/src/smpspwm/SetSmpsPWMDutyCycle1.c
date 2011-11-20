#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF 


/*************************************************************************
* Function Name     : SetSmpsPWMDutyCycle1
* Description       : This function Provides the duty cycle value for the 
*					  PWM1H output or PWM1H and PWM1L outputs if shared time base is selected
*					  if defined(__dsPIC33F__)					  
*					  Provides the duty cycle value for the PWM1H output if independent 
*					  time base is selected                       
* Parameters        : unsigned int dutycycle
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMDutyCycle1(unsigned int dutycycle )
{
    PDC1 = dutycycle ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
