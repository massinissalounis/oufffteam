#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM3IF)
/*************************************************************************
* Function Name     : SetHSPWMLebTime3
* Description       : This function configures the assignment of Leading edge blanking 
*                     units to rising edge or falling edge of PWM3 output                         
* Parameters        : unsigned int leb
* Return Value      : None 
**************************************************************************/

void SetHSPWMLebTime3(unsigned int leb )
{
    LEBDLY3 = leb ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
