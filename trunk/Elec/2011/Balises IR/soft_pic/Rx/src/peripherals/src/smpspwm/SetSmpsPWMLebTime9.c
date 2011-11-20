#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF
#ifdef _PWM9IF 

/*************************************************************************
* Function Name     : SetSmpsPWMLebTime9
* Description       : This function configures the assignment of Leading edge blanking 
*                     units to rising edge or falling edge of PWM9 output                        
* Parameters        : unsigned int leb, leb2
* Return Value      : None 
**************************************************************************/
void SetSmpsPWMLebTime9(unsigned int leb1, unsigned int leb2)
{
    LEBCON9 = leb1; 
    LEBDLY9 = leb2;	
}

#else
#warning "Does not build on this target"
#endif
#endif 
