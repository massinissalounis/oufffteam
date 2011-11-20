#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM2IF)
/*************************************************************************
* Function Name     : SetHSPWMDeadTime2
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM2 output                         
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetHSPWMDeadTime2(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR2 = deadtime ; 
	ALTDTR2 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
