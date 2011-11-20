#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM6IF)
/*************************************************************************
* Function Name     : ConfigHSPWMFault6
* Description       : This function configures the different PWM6 pair faults by writing 
*                     into the FCLCON6 register. The current limit control signal and Fault 
*                     control signal sources the generation of fault.                        
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMFault6(unsigned int config1)
{
    FCLCON6 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
