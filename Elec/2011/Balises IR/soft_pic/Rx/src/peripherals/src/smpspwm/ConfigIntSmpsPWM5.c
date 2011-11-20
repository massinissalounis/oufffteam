#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _PWM5IF
#ifdef _ADCP0IF 


/*************************************************************************
* Function Name     : ConfigIntSmpsPWM1
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for PWM1                      
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntSmpsPWM5(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

    /* Clear the PWM Interrupt status Flags of PWMGEN #5 */
	ClearIntSmpsPWM5();

	/* Enable/Disable the PWM Interrupt of PWMGEN #5 */
	SetIntSmpsPWM5(pwm_intp);

	/* Set the priority of PWM interrupt for PWMGEN #5 */
	SetPriorityIntSmpsPWM5(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
#endif
