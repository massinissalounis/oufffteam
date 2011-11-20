#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#if defined(__dsPIC33F__)

#include "smpspwm.h"
#ifdef _ADCP0IF 

/*************************************************************************
* Function Name     : SetSmpsPWMSecTrigCmp1
* Description       : This function configures the Secondary Trigger compare value for generating 
*					  trigger to the ADC module for initiating a sample and conversion process or 
*					  generating trigger interrupt to PWM1L output pair                       
* Parameters        : unsigned int trigcmp_val
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMSecTrigCmp1(unsigned int trigcmp_val )
{
    STRIG1 = trigcmp_val ; 
	
}
#else
#warning "Does not build on this target"
#endif

#endif

