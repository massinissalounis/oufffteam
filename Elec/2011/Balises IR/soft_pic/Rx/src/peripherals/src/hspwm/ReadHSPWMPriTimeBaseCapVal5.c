#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM5IF)
/*************************************************************************
* Function Name     : ReadHSPWMPriTimeBaseCapVal5
* Description       : This function captures the independent time base value when a 
*					  leading edge is detected on the current-limit input and LEB processing 
*					  on the current-limit input signal is completed                       
* Parameters        : None
* Return Value      : unsigned int PWMCAP5
**************************************************************************/

unsigned int ReadHSPWMPriTimeBaseCapVal5(void)
{
	return PWMCAP5;
}
#else
#warning "Does not build on this target"
#endif
