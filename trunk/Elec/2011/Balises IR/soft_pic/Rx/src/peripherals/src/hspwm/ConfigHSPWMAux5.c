#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM5IF)
/*************************************************************************
* Function Name     : ConfigHSPWMAux5
* Description       : This function configures the Auxiliary register for PWM5
*                     by writing into the AUXCON5 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMAux5(unsigned int config1)
{
    AUXCON5 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
