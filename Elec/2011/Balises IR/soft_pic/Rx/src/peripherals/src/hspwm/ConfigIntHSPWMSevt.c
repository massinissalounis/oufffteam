#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : ConfigIntHSPWMSevtMatch
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for Special Event match                       
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntHSPWMSevtMatch(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

    /* Clear the PWM Interrupt status Flags of Special Event match */
	ClearIntHSPWMSevtMatch();

	/* Enable/Disable the PWM Interrupt of Special Event match */
	SetIntHSPWMSevtMatch(pwm_intp);

	/* Set the priority of PWM interrupt for Special Event match */
	SetPriorityIntHSPWMSevtMatch(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
