#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM6IF)
/*************************************************************************
* Function Name     : ConfigHSPWM6
* Description       : This function configures the PWM6 Pair by writing to PWMCON6, 
*                     IOCON6, PHASE6, TRGCON6 and SPHASE6 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigHSPWM6(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON6 = config1;
	IOCON6  = config2;
    PHASE6  = config3;
	TRGCON6 = config4;
    SPHASE6 = config5;
}

#else
#warning "Does not build on this target"
#endif 
