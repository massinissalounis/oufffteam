#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM7IF)
/*************************************************************************
* Function Name     : ConfigHSPWMAux7
* Description       : This function configures the Auxiliary register for PWM7
*                     by writing into the AUXCON7 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMAux7(unsigned int config1)
{
    AUXCON7 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
