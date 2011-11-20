#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM4IF)
/*************************************************************************
* Function Name     : SetHSPWMDeadTime4
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM4 output                         
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetHSPWMDeadTime4(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR4 = deadtime ; 
	ALTDTR4 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
 
