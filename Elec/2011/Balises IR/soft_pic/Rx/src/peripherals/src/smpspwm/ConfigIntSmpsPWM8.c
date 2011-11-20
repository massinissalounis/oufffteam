#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM8IF 


/*************************************************************************
* Function Name     : ConfigIntSmpsPWM4
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for PWM4                        
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntSmpsPWM8(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

     /* Clear the PWM Interrupt status Flags of PWMGEN #8 */
	ClearIntSmpsPWM8();

	/* Enable/Disable the PWM Interrupt of PWMGEN #8*/
	SetIntSmpsPWM8(pwm_intp);

	/* Set the priority of PWM interrupt for PWMGEN #8*/
	SetPriorityIntSmpsPWM8(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
#endif 
