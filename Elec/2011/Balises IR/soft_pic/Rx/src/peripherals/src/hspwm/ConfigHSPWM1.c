#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : ConfigHSPWM1
* Description       : This function configures the PWM1 Pair by writing to PWMCON1, 
*                     IOCON1, PHASE1, TRGCON1 and SPHASE1 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigHSPWM1(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON1 = config1;
	IOCON1  = config2;
    PHASE1  = config3;
    TRGCON1 = config4;
    SPHASE1 = config5;
}

#else
#warning "Does not build on this target"
#endif
