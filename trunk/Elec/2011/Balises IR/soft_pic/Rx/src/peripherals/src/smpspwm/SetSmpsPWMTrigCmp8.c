#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM8IF 


/*************************************************************************
* Function Name     : SetSmpsPWMTrigCmp1
* Description       : This function configures the Trigger compare value  for generating trigger to the 
*                     ADC module for initiating a sample and conversion process or generating 
*                     trigger interrupt to PWM8 output pair
*					  if defined(__dsPIC33F__)
*					  This function configures the Trigger compare value  for generating trigger to the 
*                     ADC module for initiating a sample and conversion process or generating 
*                     trigger interrupt to PWM8H output pair                        
* Parameters        : unsigned int trigcmp_val
* Return Value      : None 
**************************************************************************/

void SetSmpsPWMTrigCmp8(unsigned int trigcmp_val )
{
    TRIG8 = trigcmp_val ; 
	
}
#else
#warning "Does not build on this target"
#endif
#endif 
