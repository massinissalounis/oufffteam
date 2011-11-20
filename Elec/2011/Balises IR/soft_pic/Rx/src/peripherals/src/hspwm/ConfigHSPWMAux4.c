#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM4IF)
/*************************************************************************
* Function Name     : ConfigHSPWMAux4
* Description       : This function configures the Auxiliary register for PWM4
*                     by writing into the AUXCON4 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMAux4(unsigned int config1)
{
    AUXCON4 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
