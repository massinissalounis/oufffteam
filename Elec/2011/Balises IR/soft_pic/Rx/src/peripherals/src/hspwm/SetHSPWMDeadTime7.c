#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM7IF)
/*************************************************************************
* Function Name     : SetHSPWMDeadTime7
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM7 output                         
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetHSPWMDeadTime7(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR7 = deadtime ; 
	ALTDTR7 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
 
