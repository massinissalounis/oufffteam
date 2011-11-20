#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM6IF)
/*************************************************************************
* Function Name     : SetHSPWMLebTime6
* Description       : This function configures the assignment of Leading edge blanking 
*                     units to rising edge or falling edge of PWM6 output                         
* Parameters        : unsigned int leb
* Return Value      : None 
**************************************************************************/

void SetHSPWMLebTime6(unsigned int leb )
{
    LEBDLY6 = leb ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
