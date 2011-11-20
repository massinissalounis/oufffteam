#include <pwm12.h>

#ifdef _FLTA2IF

/*********************************************************************
* Function Name     : OpenMCPWM2
* Description       : This function configures PWM2 module for the 
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

void OpenMCPWM2(unsigned int period, unsigned int sptime, unsigned int 
               config1, unsigned int config2, unsigned int config3)
{
    P2TPER   = period;
    P2SECMP  = sptime;
    PWM2CON1 = config2;
    PWM2CON2 = config3;
    P2TCON   = config1;
}

#else
#warning "Does not build on this target"
#endif
