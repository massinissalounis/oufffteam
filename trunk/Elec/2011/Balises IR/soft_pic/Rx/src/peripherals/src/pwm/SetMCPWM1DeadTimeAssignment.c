#include <pwm12.h>

#ifdef _FLTB1IF

/*************************************************************************
* Function Name     : SetMCPWM1DeadTimeAssignment
* Description       : This function configures the assignment of dead time 
*                     units to PWM1 output pairs                        
* Parameters        : unsigned int config
* Return Value      : None 
**************************************************************************/

void SetMCPWM1DeadTimeAssignment(unsigned int config)
{
    P1DTCON2 = config ; 
}

#else
#warning "Does not build on this target"
#endif
