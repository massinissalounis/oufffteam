#include <pwm12.h>

#ifdef _FLTA2IF

/*************************************************************************
* Function Name     : SetMCPWM2DeadTimeAssignment
* Description       : This function configures the assignment of dead time 
*                     units to PWM output pairs                        
* Parameters        : unsigned int config
* Return Value      : None 
**************************************************************************/

void SetMCPWM2DeadTimeAssignment(unsigned int config)
{
    P2DTCON2 = config ; 
}

#else
#warning "Does not build on this target"
#endif
