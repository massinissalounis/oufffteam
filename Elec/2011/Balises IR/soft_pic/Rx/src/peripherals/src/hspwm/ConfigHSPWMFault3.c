#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM3IF)
/*************************************************************************
* Function Name     : ConfigHSPWMFault3
* Description       : This function configures the different PWM3 pair faults by writing 
*                     into the FCLCON3 register. The current limit control signal and Fault 
*                     control signal sources the generation of fault.                        
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMFault3(unsigned int config1)
{
    FCLCON3 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
