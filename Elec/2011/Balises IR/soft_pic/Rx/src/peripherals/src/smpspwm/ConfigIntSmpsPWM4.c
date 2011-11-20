#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM4IF 


/*************************************************************************
* Function Name     : ConfigIntSmpsPWM4
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for PWM4                        
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntSmpsPWM4(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

     /* Clear the PWM Interrupt status Flags of PWMGEN #1 */
	ClearIntSmpsPWM4();

	/* Enable/Disable the PWM Interrupt of PWMGEN #1 */
	SetIntSmpsPWM4(pwm_intp);

	/* Set the priority of PWM interrupt for PWMGEN #1 */
	SetPriorityIntSmpsPWM4(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
#endif 
