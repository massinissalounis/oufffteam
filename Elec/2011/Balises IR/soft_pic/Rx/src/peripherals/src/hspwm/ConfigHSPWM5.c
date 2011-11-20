#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM5IF)
/*************************************************************************
* Function Name     : ConfigHSPWM5
* Description       : This function configures the PWM5 Pair by writing to PWMCON5, 
*                     IOCON5, PHASE5, TRGCON5 and SPHASE5 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigHSPWM5(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON5 = config1;
	IOCON5  = config2;
    PHASE5  = config3;
	TRGCON5 = config4;
    SPHASE5 = config5;
}

#else
#warning "Does not build on this target"
#endif 
