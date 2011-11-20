#include <pwm12.h>

#ifdef _FLTA2IF

/**********************************************************************
* Function Name     : SetMCPWM2FaultA
* Description       : This function sets Fault A override and enables 
*                     for pins of PWM2     
* Parameters        : unsigned int config includes the FAULT A override
*                     value, 
*                     Fault A mode, Fault A Pairs Enable
* Return Value      : None
**********************************************************************/

void SetMCPWM2FaultA(unsigned int config)
{
    P2FLTACON = config;
}

#else
#warning "Does not build on this target"
#endif
