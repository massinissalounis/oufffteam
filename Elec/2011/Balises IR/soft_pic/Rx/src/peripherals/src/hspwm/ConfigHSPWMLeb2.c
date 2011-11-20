#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM2IF)
/*************************************************************************
* Function Name     : ConfigHSPWMLeb2
* Description       : This function configures the different PWM2 pair Leading-Edge Blanking
*                     by writing into the LEBCON2 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMLeb2(unsigned int config1)
{
    LEBCON2 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
