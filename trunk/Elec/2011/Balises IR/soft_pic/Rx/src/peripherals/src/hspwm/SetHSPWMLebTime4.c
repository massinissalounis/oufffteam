#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM4IF)
/*************************************************************************
* Function Name     : SetHSPWMLebTime4
* Description       : This function configures the assignment of Leading edge blanking 
*                     units to rising edge or falling edge of PWM4 output                         
* Parameters        : unsigned int leb
* Return Value      : None 
**************************************************************************/

void SetHSPWMLebTime4(unsigned int leb )
{
    LEBDLY4 = leb ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
