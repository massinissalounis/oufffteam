#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"

#ifdef _ADCP7IF

/*************************************************************************
* Function Name     : OpenSmpsPWM
* Description       : This function configures the Power Supply PWM module.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/

void OpenSecSmpsPWM(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4)
{
    STCON   = config1 ; 
	STPER   = config2 ; 

    SSEVTCMP = config4 ; 
}

#else
#warning "Does not build on this target"
#endif



