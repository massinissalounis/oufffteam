#include <pwm12.h>

#ifdef _FLTA1IF

/*********************************************************************
* Function Name     : OpenMCPWM1
* Description       : This function configures PWM1 module for the 
*                     following parameters:
*                     period, sptime, PWM Mode, Clock Prescale,
*                     Output Postscale, high res mode, I/O pair mode, 
*                     I/O pair mode,I/O pair enable, Special event 
*                     postscale, Special event direction, override 
*                     synchronization.
* Parameters        : unsigned int period
*                     unsigned int sptime
*                     unsigned int config1
*                     unsigned int config2, 
*                     unsigned int config3
* Return Value      : None 
**********************************************************************/

void OpenMCPWM1(unsigned int period, unsigned int sptime, unsigned int 
               config1, unsigned int config2, unsigned int config3)
{
    P1TPER   = period;
    P1SECMP = sptime;
    PWM1CON1 = config2;
    PWM1CON2 = config3;
    P1TCON   = config1;
}

#else
#warning "Does not build on this target"
#endif
