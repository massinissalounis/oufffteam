#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM3IF)
/*************************************************************************
* Function Name     : ConfigHSPWM3
* Description       : This function configures the PWM3 Pair by writing to PWMCON3, 
*                     IOCON3, PHASE3, TRGCON3 and SPHASE3 registers.                       
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4,unsigned int config5
* Return Value      : None 
**************************************************************************/

void ConfigHSPWM3(unsigned int config1,unsigned int config2,unsigned int config3,
                    unsigned int config4, unsigned int config5)
{
    PWMCON3 = config1;
	IOCON3  = config2;
    PHASE3  = config3;
	TRGCON3 = config4;
    SPHASE3 = config5;
}

#else
#warning "Does not build on this target"
#endif 
