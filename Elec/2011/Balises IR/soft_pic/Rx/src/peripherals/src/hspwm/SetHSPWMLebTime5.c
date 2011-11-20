#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM5IF)
/*************************************************************************
* Function Name     : SetHSPWMLebTime5
* Description       : This function configures the assignment of Leading edge blanking 
*                     units to rising edge or falling edge of PWM5 output                         
* Parameters        : unsigned int leb
* Return Value      : None 
**************************************************************************/

void SetHSPWMLebTime5(unsigned int leb )
{
    LEBDLY5 = leb ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
