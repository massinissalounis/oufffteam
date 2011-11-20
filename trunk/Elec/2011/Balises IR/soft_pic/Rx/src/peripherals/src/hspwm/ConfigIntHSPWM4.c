#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM4IF)
/*************************************************************************
* Function Name     : ConfigIntHSPWM4
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for PWM4                      
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntHSPWM4(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

    /* Clear the PWM Interrupt status Flags of PWMGEN #4 */
	ClearIntHSPWM4();

	/* Enable/Disable the PWM Interrupt of PWMGEN #4 */
	SetIntHSPWM4(pwm_intp);

	/* Set the priority of PWM interrupt for PWMGEN #4 */
	SetPriorityIntHSPWM4(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
