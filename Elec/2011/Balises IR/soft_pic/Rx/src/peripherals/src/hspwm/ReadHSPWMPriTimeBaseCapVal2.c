#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM2IF)
/*************************************************************************
* Function Name     : ReadHSPWMPriTimeBaseCapVal2
* Description       : This function captures the independent time base value when a 
*					  leading edge is detected on the current-limit input and LEB processing 
*					  on the current-limit input signal is completed                       
* Parameters        : None
* Return Value      : unsigned int PWMCAP2
**************************************************************************/

unsigned int ReadHSPWMPriTimeBaseCapVal2(void)
{
	return PWMCAP2;
}
#else
#warning "Does not build on this target"
#endif
