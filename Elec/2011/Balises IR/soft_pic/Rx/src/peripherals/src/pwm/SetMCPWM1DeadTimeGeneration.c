#include <pwm12.h>

#ifdef _FLTA1IF

/***********************************************************************
* Function Name     : SetMCPWM1DeadTimeSourceGeneration 
* Description       : This function configures dead time values and clock                       
*					  prescalers.
* Parameters        : unsigned int config
* Return Value      : None 
************************************************************************/

void SetMCPWM1DeadTimeGeneration (unsigned int config)
{
    P1DTCON1 = config;
}

#else
#warning "Does not build on this target"
#endif
