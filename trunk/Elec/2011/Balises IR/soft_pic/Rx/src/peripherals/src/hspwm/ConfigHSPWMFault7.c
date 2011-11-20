#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM7IF)
/*************************************************************************
* Function Name     : ConfigHSPWMFault7
* Description       : This function configures the different PWM7 pair faults by writing 
*                     into the FCLCON7 register. The current limit control signal and Fault 
*                     control signal sources the generation of fault.                        
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMFault7(unsigned int config1)
{
    FCLCON7 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
