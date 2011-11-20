#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF


/*************************************************************************
* Function Name     : OpenSmpsPWM
* Description       : This function configures the Power Supply PWM module.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/

void OpenSmpsPWM(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4)
{
    PTCON   = config1 ; 
	PTPER   = config2 ; 
    MDC     = config3 ; 
    SEVTCMP = config4 ; 
}
#else
#warning "Does not build on this target"
#endif
 


