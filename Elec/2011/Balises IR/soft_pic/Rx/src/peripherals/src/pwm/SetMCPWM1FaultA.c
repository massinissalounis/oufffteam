#include <pwm12.h>

#ifdef _FLTA1IF

/**********************************************************************
* Function Name     : SetMCPWM1FaultA
* Description       : This function sets Fault A override and enables 
*                     for pins of PWM     
* Parameters        : unsigned int config includes the FAULT A override
*                     value, 
*                     Fault A mode, Fault A Pairs Enable
* Return Value      : None
**********************************************************************/

void SetMCPWM1FaultA(unsigned int config)
{
    P1FLTACON = config;
}

#else
#warning "Does not build on this target"
#endif
