#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef  _PWM5IF
#ifdef _ADCP0IF 

#if defined(__dsPIC30F__) 
/*************************************************************************
* Function Name     : ConfigSmpsPWM5
* Description       : This function configures the PWM5 Pair by writing to PWMCON5, 
*                     IOCON5, PHASE5 and TRGCON5 registers.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM5(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4)
{
    PWMCON5 = config1 ; 
	IOCON5 = config2 ; 
    PHASE5 = config3 ; 
    TRGCON5 = config4 ; 
}
#elif defined(__dsPIC33F__)

/*************************************************************************
* Function Name     : ConfigSmpsPWM5
* Description       : This function configures the PWM5 Pair by writing to PWMCON5, 
*                     IOCON5, PHASE5, TRGCON5 and SPHASE5 registers.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM5(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON5= config1 ; 
	IOCON5  = config2 ; 
    PHASE5  = config3 ; 
	TRGCON5 = config4 ;
    SPHASE5 = config5 ; 
}
#endif

#else
#warning "Does not build on this target"
#endif
 #endif
