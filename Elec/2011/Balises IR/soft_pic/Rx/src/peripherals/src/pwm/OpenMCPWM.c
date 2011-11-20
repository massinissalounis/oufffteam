#include <pwm.h>

#ifdef _PWMIF

/*********************************************************************
* Function Name     : OpenMCPWM
* Description       : This function configures PWM module for the 
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

void OpenMCPWM(unsigned int period, unsigned int sptime, unsigned int 
               config1, unsigned int config2, unsigned int config3)
{
    PTPER   = period;
    SEVTCMP = sptime;
    PWMCON1 = config2;
    PWMCON2 = config3;
    PTCON   = config1;
}

#else
#warning "Does not build on this target"
#endif
