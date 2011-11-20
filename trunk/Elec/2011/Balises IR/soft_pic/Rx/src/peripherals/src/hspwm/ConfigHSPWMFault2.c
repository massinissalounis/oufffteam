#include <hspwm.h>

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_PWM2IF)
/*************************************************************************
* Function Name     : ConfigHSPWMFault2
* Description       : This function configures the different PWM2 pair faults by writing 
*                     into the FCLCON2 register. The current limit control signal and Fault 
*                     control signal sources the generation of fault.                        
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigHSPWMFault2(unsigned int config1)
{
    FCLCON2 = config1;
}
#else
#warning "Does not build on this target"
#endif
 
