#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : SetHSPWMChop
* Description       : This function Provides the CHOP value for the 
*					  PWM Module
* Parameters        : unsigned int config1, unsigned int config2
* Return Value      : None 
**************************************************************************/

void SetHSPWMChop(unsigned int config1, unsigned int config2)
{
	_CHPCLKEN = config1;
    _CHOPCLK = config2;
}
#else
#warning "Does not build on this target"
#endif
 
