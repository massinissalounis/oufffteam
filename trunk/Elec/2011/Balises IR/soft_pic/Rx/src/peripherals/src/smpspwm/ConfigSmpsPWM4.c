#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM4IF 


#if defined(__dsPIC30F__) 

/*************************************************************************
* Function Name     : ConfigSmpsPWM4
* Description       : This function configures the PWM4 Pair by writing to PWMCON4, 
*                     IOCON4, PHASE4 and TRGCON4 registers.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM4(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4)
{
    PWMCON4 = config1 ; 
	IOCON4  = config2 ; 
    PHASE4  = config3 ; 
    TRGCON4 = config4 ; 
}

#elif defined(__dsPIC33F__)

/*************************************************************************
* Function Name     : ConfigSmpsPWM4
* Description       : This function configures the PWM4 Pair by writing to PWMCON4, 
*                     IOCON4, PHASE4, TRGCON4 and SPHASE4 registers.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM4(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON4 = config1 ; 
	IOCON4  = config2 ; 
    PHASE4  = config3 ; 
	TRGCON4 = config4 ;
    SPHASE4 = config5 ; 
}
#endif

#else
#warning "Does not build on this target"
#endif
#endif 
