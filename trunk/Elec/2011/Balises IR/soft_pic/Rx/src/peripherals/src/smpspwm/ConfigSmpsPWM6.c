#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM6IF 



#if defined(__dsPIC30F__) 

/*************************************************************************
* Function Name     : ConfigSmpsPWM6
* Description       : This function configures the PWM6 Pair by writing to PWMCON6, 
*                     IOCON6, PHASE6 and TRGCON6 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/
void ConfigSmpsPWM6(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4)
{
    PWMCON6 = config1 ; 
	IOCON6  = config2 ; 
    PHASE6 = config3 ; 
    TRGCON6 = config4 ; 
}

#elif defined(__dsPIC33F__)

/*************************************************************************
* Function Name     : ConfigSmpsPWM6
* Description       : This function configures the PWM6 Pair by writing to PWMCON6, 
*                     IOCON6, PHASE6, TRGCON6 and SPHASE6 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM6(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON6 = config1 ; 
	IOCON6  = config2 ; 
    PHASE6 = config3 ; 
	TRGCON6 = config4 ;
    SPHASE6 = config5 ; 
}
#endif

#else
#warning "Does not build on this target"
#endif
#endif 
