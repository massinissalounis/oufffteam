#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM4IF)
/*************************************************************************
* Function Name     : ConfigHSPWM4
* Description       : This function configures the PWM4 Pair by writing to PWMCON4, 
*                     IOCON4, PHASE4, TRGCON4 and SPHASE4 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigHSPWM4(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON4 = config1;
	IOCON4  = config2;
    PHASE4  = config3;
	TRGCON4 = config4;
    SPHASE4 = config5;
}

#else
#warning "Does not build on this target"
#endif 
