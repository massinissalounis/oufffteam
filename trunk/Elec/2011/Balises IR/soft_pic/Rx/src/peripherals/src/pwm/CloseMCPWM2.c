#include <pwm12.h>

#ifdef _FLTA2IF

/***********************************************************************
* Function Name     : CloseMCPWM2
* Description       : This function Clears the Interrupt enable ,flag 
*                     bits, P2TCON, PWM2CON1 and PWM2CON2 registers. 
* Parameters        : void
* Return Value      : void 
**********************************************************************/

void CloseMCPWM2(void)
{
    /* clear the Interrupt enables */
    _PWM2IE = 0;	
    _FLTA2IE = 0;


    /* clear the Interrupt flags */
    _PWM2IF = 0;	
    _FLTA2IF = 0;


    /* clear the PWM control registers */
    P2TCON       =       0;
    PWM2CON1     =       0;
    PWM2CON2     =       0;
}
#else
#warning "Does not build on this target"
#endif
