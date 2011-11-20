#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : SetHSPWMLebTime1
* Description       : This function configures the assignment of Leading edge blanking 
*                     units to rising edge or falling edge of PWM1 output                         
* Parameters        : unsigned int leb
* Return Value      : None 
**************************************************************************/

void SetHSPWMLebTime1(unsigned int leb )
{
    LEBDLY1 = leb ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
