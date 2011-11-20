#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM2IF 



#if defined(__dsPIC30F__) 

/*************************************************************************
* Function Name     : ConfigSmpsPWM2
* Description       : This function configures the PWM2 Pair by writing to PWMCON2, 
*                     IOCON2, PHASE2 and TRGCON2 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/
void ConfigSmpsPWM2(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4)
{
    PWMCON2 = config1 ; 
	IOCON2  = config2 ; 
    PHASE2  = config3 ; 
    TRGCON2 = config4 ; 
}

#elif defined(__dsPIC33F__)

/*************************************************************************
* Function Name     : ConfigSmpsPWM2
* Description       : This function configures the PWM2 Pair by writing to PWMCON2, 
*                     IOCON2, PHASE2, TRGCON2 and SPHASE2 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM2(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON2 = config1 ; 
	IOCON2  = config2 ; 
    PHASE2  = config3 ; 
	TRGCON2 = config4 ;
    SPHASE2 = config5 ; 
}
#endif

#else
#warning "Does not build on this target"
#endif
#endif 
