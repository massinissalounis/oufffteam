#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM7IF)
/*************************************************************************
* Function Name     : ConfigHSPWMLeb7
* Description       : This function configures the different PWM7 pair Leading-Edge Blanking
*                     by writing into the LEBCON7 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMLeb7(unsigned int config1)
{
    LEBCON7 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
