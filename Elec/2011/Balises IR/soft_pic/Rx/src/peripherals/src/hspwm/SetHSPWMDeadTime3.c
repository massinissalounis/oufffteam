#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM3IF)
/*************************************************************************
* Function Name     : SetHSPWMDeadTime3
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM3 output                         
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetHSPWMDeadTime3(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR3 = deadtime ; 
	ALTDTR3 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
 
