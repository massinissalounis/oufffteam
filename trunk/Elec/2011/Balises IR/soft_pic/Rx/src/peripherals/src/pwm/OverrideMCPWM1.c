#include <pwm12.h>

#ifdef _FLTA1IF

/*********************************************************************
* Function Name     : OverrideMCPWM1
* Description       : This function set P1OVDCON register includes PWM1 
*                     output override bits and PWM Manual Output Bits
* Parameters        : unsigned int config
* Return Value      : None 
*********************************************************************/

void OverrideMCPWM1(unsigned int config)
{
    P1OVDCON = config;
}

#else
#warning "Does not build on this target"
#endif
