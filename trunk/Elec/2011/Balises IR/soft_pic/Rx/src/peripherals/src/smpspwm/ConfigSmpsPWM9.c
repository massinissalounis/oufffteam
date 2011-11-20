#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM9IF 


#if defined(__dsPIC30F__) 

/*************************************************************************
* Function Name     : ConfigSmpsPWM9
* Description       : This function configures the PWM9 Pair by writing to PWMCON9, 
*                     IOCON9, PHASE9 and TRGCON9 registers.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM9(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4)
{
    PWMCON9 = config1 ; 
	IOCON9  = config2 ; 
    PHASE9  = config3 ; 
    TRGCON9 = config4 ; 
}

#elif defined(__dsPIC33F__)

/*************************************************************************
* Function Name     : ConfigSmpsPWM9
* Description       : This function configures the PWM9 Pair by writing to PWMCON9, 
*                     IOCON9, PHASE9, TRGCON9 and SPHASE9 registers.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM9(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON9 = config1 ; 
	IOCON9  = config2 ; 
    PHASE9  = config3 ; 
	TRGCON9 = config4 ;
    SPHASE9 = config5 ; 
}
#endif

#else
#warning "Does not build on this target"
#endif
#endif 
