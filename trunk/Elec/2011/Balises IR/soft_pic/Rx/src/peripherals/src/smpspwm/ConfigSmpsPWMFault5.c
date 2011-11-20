#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF 
#ifdef _PWM5IF

/*************************************************************************
* Function Name     : ConfigSmpsPWMFault5
* Description       : This function configures the different PWM1 pair faults by writing 
*                     into the FCLCON5 register. The current limit control signal and Fault 
*                     control signal sources the generation of fault.                        
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWMFault5(unsigned int config1)
{
    FCLCON5 = config1 ; 
	
}
#else
#warning "Does not build on this target"
#endif
 #endif
