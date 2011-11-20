#include <pwm12.h>

#ifdef _FLTA2IF

/***********************************************************************
* Function Name     : SetMCPWM2DeadTimeSourceGeneration 
* Description       : This function configures dead time values and clock                       
*					  prescalers.
* Parameters        : unsigned int config
* Return Value      : None 
************************************************************************/

void SetMCPWM2DeadTimeGeneration (unsigned int config)
{
    P2DTCON1 = config;
}

#else
#warning "Does not build on this target"
#endif
