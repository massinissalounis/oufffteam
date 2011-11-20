#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : ConfigHSPWMAux1
* Description       : This function configures the Auxiliary register for PWM1
*                     by writing into the AUXCON1 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMAux1(unsigned int config1)
{
    AUXCON1 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
