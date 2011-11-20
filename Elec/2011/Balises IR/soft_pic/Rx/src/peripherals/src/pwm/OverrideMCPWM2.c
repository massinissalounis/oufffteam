#include <pwm12.h>

#ifdef _FLTA2IF

/*********************************************************************
* Function Name     : OverrideMCPWM2
* Description       : This function set P2OVDCON register includes PWM2 
*                     output override bits and PWM Manual Output Bits
* Parameters        : unsigned int config
* Return Value      : None 
*********************************************************************/

void OverrideMCPWM2(unsigned int config)
{
    P2OVDCON = config;
}

#else
#warning "Does not build on this target"
#endif
