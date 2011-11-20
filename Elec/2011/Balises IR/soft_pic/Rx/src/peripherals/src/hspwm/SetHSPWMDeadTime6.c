#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM6IF)
/*************************************************************************
* Function Name     : SetHSPWMDeadTime6
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM6 output                         
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetHSPWMDeadTime6(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR6 = deadtime ; 
	ALTDTR6 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
 
