#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM7IF)
/*************************************************************************
* Function Name     : SetHSPWMLebTime7
* Description       : This function configures the assignment of Leading edge blanking 
*                     units to rising edge or falling edge of PWM7 output                         
* Parameters        : unsigned int leb
* Return Value      : None 
**************************************************************************/

void SetHSPWMLebTime7(unsigned int leb )
{
    LEBDLY7 = leb ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
