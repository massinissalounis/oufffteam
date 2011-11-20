#include <pwm.h>

#ifdef _PWMIF

/*********************************************************************
* Function Name     : OverrideMCPWM
* Description       : This function set OVDCON register includes PWM 
*                     output override bits and PWM Manual Output Bits
* Parameters        : unsigned int config
* Return Value      : None 
*********************************************************************/

void OverrideMCPWM(unsigned int config)
{
    OVDCON = config;
}

#else
#warning "Does not build on this target"
#endif
