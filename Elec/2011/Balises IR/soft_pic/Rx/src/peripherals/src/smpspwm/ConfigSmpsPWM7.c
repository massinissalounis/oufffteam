#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM7IF 


#if defined(__dsPIC30F__)

/*************************************************************************
* Function Name     : ConfigSmpsPWM7
* Description       : TThis function configures the PWM7 Pair by writing to PWMCON7, 
*                     IOCON7, PHASE7 and TRGCON7 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/
void ConfigSmpsPWM7(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4)
{
    PWMCON7 = config1 ; 
	IOCON7  = config2 ; 
    PHASE7  = config3 ; 
    TRGCON7 = config4 ; 
}

#elif defined(__dsPIC33F__)

/*************************************************************************
* Function Name     : ConfigSmpsPWM7
* Description       : TThis function configures the PWM7 Pair by writing to PWMCON7, 
*                     IOCON7, PHASE7, TRGCON7 and SPHASE7 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM7(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON7 = config1 ; 
	IOCON7  = config2 ; 
    PHASE7  = config3 ; 
	TRGCON7 = config4 ;
    SPHASE7 = config5 ; 
}
#endif

#else
#warning "Does not build on this target"
#endif
#endif 
