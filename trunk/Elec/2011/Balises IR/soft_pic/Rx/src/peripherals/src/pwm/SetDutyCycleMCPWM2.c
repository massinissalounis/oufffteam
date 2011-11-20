#include <pwm12.h>

#ifdef _FLTA2IF

/*********************************************************************
* Function Name     : SetDCMCPWM2
* Description       : This function updates the dutycycle register and 
*                     updatedisable bit.
* Parameters        : unsigned int dutycycle
*                     char updatedisable
* Return Value      : None 
**********************************************************************/

void SetDCMCPWM2(unsigned int dutycycle,
                char updatedisable)
{
    PWM2CON2bits.UDIS = updatedisable & 0x1;
    
    /* Assign dutycycle to the duty cycle register */
    *(&P2DC1) = dutycycle; 
}

#else
#warning "Does not build on this target"
#endif
