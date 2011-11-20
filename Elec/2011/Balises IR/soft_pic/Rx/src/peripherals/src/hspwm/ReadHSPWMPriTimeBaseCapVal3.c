#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM3IF)
/*************************************************************************
* Function Name     : ReadHSPWMPriTimeBaseCapVal3
* Description       : This function captures the independent time base value when a 
*					  leading edge is detected on the current-limit input and LEB processing 
*					  on the current-limit input signal is completed                       
* Parameters        : None
* Return Value      : unsigned int PWMCAP3
**************************************************************************/

unsigned int ReadHSPWMPriTimeBaseCapVal3(void)
{
	return PWMCAP3;
}
#else
#warning "Does not build on this target"
#endif
