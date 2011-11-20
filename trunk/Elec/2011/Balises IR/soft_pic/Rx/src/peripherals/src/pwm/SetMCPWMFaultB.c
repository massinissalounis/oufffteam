#include <pwm.h>

#ifdef _FLTBIF

/**********************************************************************
* Function Name     : SetMCPWMFaultB
* Description       : This function sets Fault B override and enables 
*                     for pins of PWM     
* Parameters        : unsigned int config includes the FAULT B override
*                     value, 
*                     Fault B mode, Fault B Pairs Enable
* Return Value      : None 
***********************************************************************/

void SetMCPWMFaultB(unsigned int config)
{
   FLTBCON = config; 
}

#else
#warning "Does not build on this target"
#endif
