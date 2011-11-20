#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM2IF)
/*************************************************************************
* Function Name     : SetHSPWMLebTime2
* Description       : This function configures the assignment of Leading edge blanking 
*                     units to rising edge or falling edge of PWM2 output                         
* Parameters        : unsigned int leb
* Return Value      : None 
**************************************************************************/

void SetHSPWMLebTime2(unsigned int leb )
{
    LEBDLY2 = leb ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
