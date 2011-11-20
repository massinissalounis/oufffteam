#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM5IF)
/*************************************************************************
* Function Name     : ConfigIntHSPWM5
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for PWM5                      
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntHSPWM5(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

    /* Clear the PWM Interrupt status Flags of PWMGEN #5 */
	ClearIntHSPWM5();

	/* Enable/Disable the PWM Interrupt of PWMGEN #5 */
	SetIntHSPWM5(pwm_intp);

	/* Set the priority of PWM interrupt for PWMGEN #5 */
	SetPriorityIntHSPWM5(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
