#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM5IF)
/*************************************************************************
* Function Name     : ConfigHSPWMFault5
* Description       : This function configures the different PWM5 pair faults by writing 
*                     into the FCLCON5 register. The current limit control signal and Fault 
*                     control signal sources the generation of fault.                        
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMFault5(unsigned int config1)
{
    FCLCON5 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
