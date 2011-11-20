#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM4IF 


/*************************************************************************
* Function Name     : SetSmpsPWMDeadTime4
* Description       : This function configures the assignment of dead time 
*                     and alternate dead time units to PWM4 output                        
* Parameters        : unsigned int deadtime, unsigned int altdeadtime
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMDeadTime4(unsigned int deadtime,unsigned int altdeadtime )
{
    DTR4 = deadtime ; 
	ALTDTR4 = altdeadtime ;
}
#else
#warning "Does not build on this target"
#endif
#endif
