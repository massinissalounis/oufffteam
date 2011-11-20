#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM5IF)
/*************************************************************************
* Function Name     : ConfigHSPWMLeb5
* Description       : This function configures the different PWM5 pair Leading-Edge Blanking
*                     by writing into the LEBCON5 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMLeb5(unsigned int config1)
{
    LEBCON5 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
