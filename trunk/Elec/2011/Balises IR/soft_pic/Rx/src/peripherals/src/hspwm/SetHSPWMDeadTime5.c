#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM5IF)
/*************************************************************************
* Function Name     : SetHSPWMDeadTime5
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM5 output                         
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetHSPWMDeadTime5(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR5 = deadtime ; 
	ALTDTR5 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
 
