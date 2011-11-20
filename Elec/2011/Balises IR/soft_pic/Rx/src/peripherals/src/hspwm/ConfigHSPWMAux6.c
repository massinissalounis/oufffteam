#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM6IF)
/*************************************************************************
* Function Name     : ConfigHSPWMAux6
* Description       : This function configures the Auxiliary register for PWM6
*                     by writing into the AUXCON6 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMAux6(unsigned int config1)
{
    AUXCON6 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
