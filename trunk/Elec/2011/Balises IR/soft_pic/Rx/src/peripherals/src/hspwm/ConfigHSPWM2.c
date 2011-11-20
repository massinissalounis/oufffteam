#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : ConfigHSPWM2
* Description       : This function configures the PWM2 Pair by writing to PWMCON2, 
*                     IOCON2, PHASE2, TRGCON2 and SPHASE2 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigHSPWM2(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON2 = config1;
	IOCON2  = config2;
    PHASE2  = config3;
	TRGCON2 = config4;
    SPHASE2 = config5;
}

#else
#warning "Does not build on this target"
#endif 
