#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM4IF)
/*************************************************************************
* Function Name     : ConfigHSPWMFault4
* Description       : This function configures the different PWM4 pair faults by writing 
*                     into the FCLCON4 register. The current limit control signal and Fault 
*                     control signal sources the generation of fault.                        
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMFault4(unsigned int config1)
{
    FCLCON4 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
