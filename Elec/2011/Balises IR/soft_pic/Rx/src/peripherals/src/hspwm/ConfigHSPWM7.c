#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM7IF)
/*************************************************************************
* Function Name     : ConfigHSPWM7
* Description       : This function configures the PWM7 Pair by writing to PWMCON7, 
*                     IOCON7, PHASE7, TRGCON7 and SPHASE7 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigHSPWM7(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON7 = config1;
	IOCON7  = config2;
    PHASE7  = config3;
	TRGCON7 = config4;
    SPHASE7 = config5;
}

#else
#warning "Does not build on this target"
#endif 
