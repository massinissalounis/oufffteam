#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM8IF 


#if defined(__dsPIC30F__) 

/*************************************************************************
* Function Name     : ConfigSmpsPWM8
* Description       : This function configures the PWM8 Pair by writing to PWMCON8, 
*                     IOCON8, PHASE8 and TRGCON8 registers.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM8(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4)
{
    PWMCON8 = config1 ; 
	IOCON8  = config2 ; 
    PHASE8  = config3 ; 
    TRGCON8 = config4 ; 
}

#elif defined(__dsPIC33F__)

/*************************************************************************
* Function Name     : ConfigSmpsPWM8
* Description       : This function configures the PWM8 Pair by writing to PWMCON8, 
*                     IOCON8, PHASE8, TRGCON8 and SPHASE8 registers.                        
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM8(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON8 = config1 ; 
	IOCON8  = config2 ; 
    PHASE8  = config3 ; 
	TRGCON8 = config4 ;
    SPHASE8 = config5 ; 
}
#endif

#else
#warning "Does not build on this target"
#endif
#endif 
