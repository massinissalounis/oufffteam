#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM3IF)
/*************************************************************************
* Function Name     : ConfigHSPWMLeb3
* Description       : This function configures the different PWM3 pair Leading-Edge Blanking
*                     by writing into the LEBCON3 register.
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMLeb3(unsigned int config1)
{
    LEBCON3 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
