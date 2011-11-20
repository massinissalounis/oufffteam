#include <pwm12.h>

#ifdef _FLTA1IF

/***********************************************************************
* Function Name     : CloseMCPWM1
* Description       : This function Clears the Interrupt enable ,flag 
*                     bits, P1TCON, PWM1CON1 and PWM1CON2 registers. 
* Parameters        : void
* Return Value      : void 
**********************************************************************/

void CloseMCPWM1(void)
{
    /* clear the Interrupt enables */
    _PWM1IE = 0;	
    _FLTA1IE = 0;

#ifdef _FLTB1IF
    _FLTB1IE = 0;	
#endif


    /* clear the Interrupt flags */
    _PWM1IF = 0;	
    _FLTA1IF = 0;

#ifdef _FLTB1IF
    _FLTB1IF = 0;
#endif

    /* clear the PWM1 control registers */
    P1TCON       =       0;
    PWM1CON1     =       0;
    PWM1CON2     =       0;
}
#else
#warning "Does not build on this target"
#endif
