#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _PSEMIF 


/*************************************************************************
* Function Name     : ConfigIntSmpsPWMSevtMatch
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for Special Event match                       
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntSmpsPWMSevtMatch(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

    /* Clear the PWM Interrupt status Flags of Special Event match */
	ClearIntSmpsPWMSevtMatch();

	/* Enable/Disable the PWM Interrupt of Special Event match */
	SetIntSmpsPWMSevtMatch(pwm_intp);

	/* Set the priority of PWM interrupt for Special Event match */
	SetPriorityIntSmpsPWMSevtMatch(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
