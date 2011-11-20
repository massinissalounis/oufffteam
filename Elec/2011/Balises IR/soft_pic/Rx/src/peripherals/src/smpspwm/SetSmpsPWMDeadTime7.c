#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM7IF 


/*************************************************************************
* Function Name     : SetSmpsPWMDeadTime7
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM7 output                       
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMDeadTime7(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR7 = deadtime ; 
	ALTDTR7 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
#endif 
