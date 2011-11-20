#include <pwm.h>

#ifdef _PWMIF

/***********************************************************************
* Function Name     : SetMCPWMDeadTimeSourceGeneration 
* Description       : This function configures dead time values and clock                       
*					  prescalers.
* Parameters        : unsigned int config
* Return Value      : None 
************************************************************************/

void SetMCPWMDeadTimeGeneration (unsigned int config)
{
    DTCON1 = config;
}

#else
#warning "Does not build on this target"
#endif
