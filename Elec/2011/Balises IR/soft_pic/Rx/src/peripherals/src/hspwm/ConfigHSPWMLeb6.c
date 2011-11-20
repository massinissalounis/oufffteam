#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM6IF)
/*************************************************************************
* Function Name     : ConfigHSPWMLeb6
* Description       : This function configures the different PWM6 pair Leading-Edge Blanking
*                     by writing into the LEBCON6 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMLeb6(unsigned int config1)
{
    LEBCON6 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
