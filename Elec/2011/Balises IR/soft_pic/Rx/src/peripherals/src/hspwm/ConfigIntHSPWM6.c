#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM6IF)
/*************************************************************************
* Function Name     : ConfigIntHSPWM6
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for PWM6                      
* Parameters        : unsigned int pwm_intp, unsigned int pwm_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntHSPWM6(unsigned int pwm_intp, unsigned int pwm_intp_priority)
{

    /* Clear the PWM Interrupt status Flags of PWMGEN #6 */
	ClearIntHSPWM6();

	/* Enable/Disable the PWM Interrupt of PWMGEN #6 */
	SetIntHSPWM6(pwm_intp);

	/* Set the priority of PWM interrupt for PWMGEN #6 */
	SetPriorityIntHSPWM6(pwm_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
