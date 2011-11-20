#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpspwm.h"
#ifdef _ADCP0IF 

/*************************************************************************
* Function Name     : SetSmpsPWMLebTime1
* Description       : This function configures the assignment of Leading edge blanking 
*                     units to rising edge or falling edge of PWM1 output                         
* Parameters        : unsigned int leb, or unsigned int leb1, leb2
* Return Value      : None 
**************************************************************************/
#ifdef _ADCP7IF
void SetSmpsPWMLebTime1(unsigned int leb1, unsigned int leb2 )
{
    LEBCON1 = leb1; 
    LEBDLY1 = leb2; 
}
#else
void SetSmpsPWMLebTime1(unsigned int leb)
{
    LEBCON1 = leb; 
}
#endif

#else
#warning "Does not build on this target"
#endif
 
