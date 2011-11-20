#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM1IF)
/*************************************************************************
* Function Name     : ConfigHSPWMLeb1
* Description       : This function configures the different PWM1 pair Leading-Edge Blanking
*                     by writing into the LEBCON1 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMLeb1(unsigned int config1)
{
    LEBCON1 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
