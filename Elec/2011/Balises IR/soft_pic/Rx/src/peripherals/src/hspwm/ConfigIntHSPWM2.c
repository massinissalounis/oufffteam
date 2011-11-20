#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM2IF)
/*************************************************************************
* Function Name     : ConfigIntHSPWM2
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for PWM2                      
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntHSPWM2(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

    /* Clear the PWM Interrupt status Flags of PWMGEN #2 */
	ClearIntHSPWM2();

	/* Enable/Disable the PWM Interrupt of PWMGEN #2 */
	SetIntHSPWM2(pwm_intp);

	/* Set the priority of PWM interrupt for PWMGEN #2 */
	SetPriorityIntHSPWM2(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
