#include <pwm.h>

#ifdef _FLTAIF

/**********************************************************************
* Function Name     : SetMCPWMFaultA
* Description       : This function sets Fault A override and enables 
*                     for pins of PWM     
* Parameters        : unsigned int config includes the FAULT A override
*                     value, 
*                     Fault A mode, Fault A Pairs Enable
* Return Value      : None
**********************************************************************/

void SetMCPWMFaultA(unsigned int config)
{
    FLTACON = config;
}

#else
#warning "Does not build on this target"
#endif
