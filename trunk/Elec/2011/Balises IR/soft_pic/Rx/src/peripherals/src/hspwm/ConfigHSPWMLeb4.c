#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM4IF)
/*************************************************************************
* Function Name     : ConfigHSPWMLeb4
* Description       : This function configures the different PWM4 pair Leading-Edge Blanking
*                     by writing into the LEBCON4 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMLeb4(unsigned int config1)
{
    LEBCON4 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
