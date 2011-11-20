#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : ReadHSPWMPriTimeBaseCapVal1
* Description       : This function captures the independent time base value when a 
*					  leading edge is detected on the current-limit input and LEB processing 
*					  on the current-limit input signal is completed                       
* Parameters        : None
* Return Value      : unsigned int PWMCAP1
**************************************************************************/

unsigned int ReadHSPWMPriTimeBaseCapVal1(void)
{
	return PWMCAP1;
}
#else
#warning "Does not build on this target"
#endif
