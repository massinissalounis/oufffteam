#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM7IF)
/*************************************************************************
* Function Name     : ConfigIntHSPWM7
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for PWM7                      
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntHSPWM7(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

    /* Clear the PWM Interrupt status Flags of PWMGEN #7 */
	ClearIntHSPWM7();

	/* Enable/Disable the PWM Interrupt of PWMGEN #7 */
	SetIntHSPWM7(pwm_intp);

	/* Set the priority of PWM interrupt for PWMGEN #7 */
	SetPriorityIntHSPWM7(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
