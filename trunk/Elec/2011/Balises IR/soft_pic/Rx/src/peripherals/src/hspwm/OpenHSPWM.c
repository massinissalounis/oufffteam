#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : OpenHSPWM
* Description       : This function configures the High Speed PWM module.
* Parameters        : unsigned int config1,unsigned int config2,unsigned int config3,
*                     unsigned int config4
* Return Value      : None 
**************************************************************************/

void OpenHSPWM(unsigned int config1,unsigned int config2,unsigned int config3,
               unsigned int config4)
{
    PTCON   = config1;
    PTCON2  = config2;
	PTPER   = config3;
    SEVTCMP = config4;
}
#else
#warning "Does not build on this target"
#endif
