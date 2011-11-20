#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : SetHSPWMDeadTime1
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM1 output                         
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetHSPWMDeadTime1(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR1 = deadtime ; 
	ALTDTR1 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
 
