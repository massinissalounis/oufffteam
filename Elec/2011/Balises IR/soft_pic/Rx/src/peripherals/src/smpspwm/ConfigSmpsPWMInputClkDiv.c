#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#if defined(__dsPIC33F__)

#include "smpspwm.h"
#ifdef _ADCP0IF

/*************************************************************************
* Function Name     : ConfigSmpsPWMInputClkDiv
* Description       : This function Provides the PWM Input Clock Prescaler(Divider)of 1:1 to 1:64  
*                     to the PWM master time base                   
* Parameters        : unsigned int prescaler_val
* Return Value      : None 
**************************************************************************/

void ConfigSmpsPWMInputClkDiv(unsigned int prescaler_val )
{
    PTCON2 = prescaler_val ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
#endif
