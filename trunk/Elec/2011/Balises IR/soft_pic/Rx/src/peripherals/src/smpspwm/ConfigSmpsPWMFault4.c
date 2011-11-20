#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM4IF 


/*************************************************************************
* Function Name     : ConfigSmpsPWMFault4
* Description       : This function configures the different PWM4 pair faults by writing 
*                     into the FCLCON4 register. The current limit control signal and Fault 
*                     control signal sources the generation of fault.                         
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWMFault4(unsigned int config1)
{
    FCLCON4 = config1 ; 
	
}
#else
#warning "Does not build on this target"
#endif
#endif 
