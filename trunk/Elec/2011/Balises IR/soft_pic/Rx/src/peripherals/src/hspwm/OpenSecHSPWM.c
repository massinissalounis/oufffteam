#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : OpenSecHSPWM
* Description       : This function configures the Secondary High Speed PWM module.
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/

void OpenSecHSPWM(unsigned int config1,unsigned int config2,unsigned int config3,
                  unsigned int config4)
{
    STCON   = config1;
	STCON2 = config2;
	STPER   = config3;
    SSEVTCMP = config4;
}
#else
#warning "Does not build on this target"
#endif
