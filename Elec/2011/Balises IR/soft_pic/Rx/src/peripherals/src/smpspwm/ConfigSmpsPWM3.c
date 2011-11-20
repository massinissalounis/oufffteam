#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM3IF 


#if defined(__dsPIC30F__)

/*************************************************************************
* Function Name     : ConfigSmpsPWM3
* Description       : TThis function configures the PWM3 Pair by writing to PWMCON3, 
*                     IOCON3, PHASE3 and TRGCON3 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/
void ConfigSmpsPWM3(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4)
{
    PWMCON3 = config1 ; 
	IOCON3  = config2 ; 
    PHASE3  = config3 ; 
    TRGCON3 = config4 ; 
}

#elif defined(__dsPIC33F__)

/*************************************************************************
* Function Name     : ConfigSmpsPWM3
* Description       : TThis function configures the PWM3 Pair by writing to PWMCON3, 
*                     IOCON3, PHASE3, TRGCON3 and SPHASE3 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWM3(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON3 = config1 ; 
	IOCON3  = config2 ; 
    PHASE3  = config3 ; 
	TRGCON3 = config4 ;
    SPHASE3 = config5 ; 
}
#endif

#else
#warning "Does not build on this target"
#endif
#endif 
