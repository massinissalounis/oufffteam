#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM3IF)
/*************************************************************************
* Function Name     : ConfigIntHSPWM3
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for PWM3                      
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntHSPWM3(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

    /* Clear the PWM Interrupt status Flags of PWMGEN #3 */
	ClearIntHSPWM3();

	/* Enable/Disable the PWM Interrupt of PWMGEN #3 */
	SetIntHSPWM3(pwm_intp);

	/* Set the priority of PWM interrupt for PWMGEN #3 */
	SetPriorityIntHSPWM3(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
