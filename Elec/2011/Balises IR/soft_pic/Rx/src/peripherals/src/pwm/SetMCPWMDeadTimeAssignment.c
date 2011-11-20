#include <pwm.h>

#ifdef _FLTBIF

/*************************************************************************
* Function Name     : SetMCPWMDeadTimeAssignment
* Description       : This function configures the assignment of dead time 
*                     units to PWM output pairs                        
* Parameters        : unsigned int config
* Return Value      : None 
**************************************************************************/

void SetMCPWMDeadTimeAssignment(unsigned int config)
{
    DTCON2 = config ; 
}

#else
#warning "Does not build on this target"
#endif
