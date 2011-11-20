#include <pwm.h>

#ifdef _PWMIF

/*********************************************************************
* Function Name     : SetDCMCPWM
* Description       : This function updates the dutycycle register and 
*                     updatedisable bit.
* Parameters        : unsigned int dutycyclereg for selection of reg
*                      (ie PDC1, PDC2...)
*                     unsigned int dutycycle
*                     char updatedisable
* Return Value      : None 
**********************************************************************/

void SetDCMCPWM(unsigned int dutycyclereg, unsigned int dutycycle,
                char updatedisable)
{
    PWMCON2bits.UDIS = updatedisable & 0x1;
    
    /* Assign dutycycle to the duty cycle register */
    *(&PDC1+dutycyclereg -1) = dutycycle; 
}

#else
#warning "Does not build on this target"
#endif
