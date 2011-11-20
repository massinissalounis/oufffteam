#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF 


/*************************************************************************
* Function Name     : SetSmpsPWMDeadTime1
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM1 output                         
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMDeadTime1(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR1 = deadtime ; 
	ALTDTR1 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
 
