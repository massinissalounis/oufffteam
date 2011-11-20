#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM3IF 


/*************************************************************************
* Function Name     : SetSmpsPWMDeadTime3
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM3 output                       
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMDeadTime3(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR3 = deadtime ; 
	ALTDTR3 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
#endif 
