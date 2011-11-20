#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM9IF 


/*************************************************************************
* Function Name     : SetSmpsPWMDeadTime9
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM9 output                       
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMDeadTime9(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR9 = deadtime ; 
	ALTDTR9 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
#endif 
