#include <pwm12.h>

#ifdef _FLTB1IF

/**********************************************************************
* Function Name     : SetMCPWM1FaultB
* Description       : This function sets Fault B override and enables 
*                     for pins of PWM1     
* Parameters        : unsigned int config includes the FAULT B override
*                     value, 
*                     Fault B mode, Fault B Pairs Enable
* Return Value      : None 
***********************************************************************/

void SetMCPWM1FaultB(unsigned int config)
{
   P1FLTBCON = config; 
}

#else
#warning "Does not build on this target"
#endif
