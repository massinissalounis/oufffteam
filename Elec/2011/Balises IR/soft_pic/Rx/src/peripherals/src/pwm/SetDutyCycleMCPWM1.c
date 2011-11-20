#include <pwm12.h>

#ifdef _FLTA1IF

/*********************************************************************
* Function Name     : SetDCMCPWM1
* Description       : This function updates the dutycycle register and 
*                     updatedisable bit.
* Parameters        : unsigned int dutycyclereg for selection of reg
*                      (ie PDC1, PDC2...)
*                     unsigned int dutycycle
*                     char updatedisable
* Return Value      : None 
**********************************************************************/

void SetDCMCPWM1(unsigned int dutycyclereg, unsigned int dutycycle,
                char updatedisable)
{
    PWM1CON2bits.UDIS = updatedisable & 0x1;
    
    /* Assign dutycycle to the duty cycle register */
    *(&P1DC1+dutycyclereg -1) = dutycycle; 
}

#else
#warning "Does not build on this target"
#endif
