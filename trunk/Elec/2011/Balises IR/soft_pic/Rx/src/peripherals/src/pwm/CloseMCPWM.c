#include <pwm.h>

#ifdef _PWMIF

/***********************************************************************
* Function Name     : CloseMCPWM
* Description       : This function Clears the Interrupt enable ,flag 
*                     bits, PTCON, PWMCON1 and PWMCON2 registers. 
* Parameters        : void
* Return Value      : void 
**********************************************************************/

void CloseMCPWM(void)
{
    /* clear the Interrupt enables */
    _PWMIE = 0;	
    _FLTAIE = 0;

#ifdef _FLTBIF
    _FLTBIE = 0;	
#endif


    /* clear the Interrupt flags */
    _PWMIF = 0;	
    _FLTAIF = 0;

#ifdef _FLTBIF
    _FLTBIF = 0;
#endif

    /* clear the PWM control registers */
    PTCON       =       0;
    PWMCON1     =       0;
    PWMCON2     =       0;
}
#else
#warning "Does not build on this target"
#endif
