#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : ConfigIntHSPWM1
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for PWM1                      
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntHSPWM1(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

    /* Clear the PWM Interrupt status Flags of PWMGEN #1 */
	ClearIntHSPWM1();

	/* Enable/Disable the PWM Interrupt of PWMGEN #1 */
	SetIntHSPWM1(pwm_intp);

	/* Set the priority of PWM interrupt for PWMGEN #1 */
	SetPriorityIntHSPWM1(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
