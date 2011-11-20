#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF 

#if defined(__dsPIC30F__) 
/*************************************************************************
* Function Name     : ConfigSmpsPWM1
* Description       : This function configures the PWM1 Pair by writing to PWMCON1, 
*                     IOCON1, PHASE1 and TRGCON1 registers.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM1(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4)
{
    PWMCON1 = config1 ; 
	IOCON1  = config2 ; 
    PHASE1  = config3 ; 
    TRGCON1 = config4 ; 
}
#elif defined(__dsPIC33F__)

/*************************************************************************
* Function Name     : ConfigSmpsPWM1
* Description       : This function configures the PWM1 Pair by writing to PWMCON1, 
*                     IOCON1, PHASE1, TRGCON1 and SPHASE1 registers.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM1(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON1 = config1 ; 
	IOCON1  = config2 ; 
    PHASE1  = config3 ; 
	TRGCON1 = config4 ;
    SPHASE1 = config5 ; 
}
#endif

#else
#warning "Does not build on this target"
#endif
 
