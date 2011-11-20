#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM3IF)
/*************************************************************************
* Function Name     : ConfigHSPWMAux3
* Description       : This function configures the Auxiliary register for PWM3
*                     by writing into the AUXCON3 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMAux3(unsigned int config1)
{
    AUXCON3 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
