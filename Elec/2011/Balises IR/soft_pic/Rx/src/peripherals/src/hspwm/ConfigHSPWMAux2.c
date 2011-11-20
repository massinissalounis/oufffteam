#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM2IF)
/*************************************************************************
* Function Name     : ConfigHSPWMAux2
* Description       : This function configures the Auxiliary register for PWM2
*                     by writing into the AUXCON2 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMAux2(unsigned int config1)
{
    AUXCON2 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
