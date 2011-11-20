#include <pwm12.h>

#ifdef _FLTA1IF

/**********************************************************************
* Function Name     :ConfigIntMCPWM1
* Description       :This function Enable/Disable interrupts and 
*                    sets Interrupt priority for period match, 
*                    FaultA and FaultB.  
* Parameters        :unsigned int Config
* Return Value      :None 
**********************************************************************/

void ConfigIntMCPWM1(unsigned int config)
{

    /* clear the Interrupt flags */
    _PWM1IF = 0;	
    _FLTA1IF = 0;	

    /* Set priority for the period match */
    _PWM1IP      = (0x0007 & config);

    /* Set priority for the Fault A */
    _FLTA1IP    = (0x0070 & config)>> 4;

    /* enable /disable of interrupt Period match */
    _PWM1IE      = (0x0008 & config) >> 3;

    /* enable /disable of interrupt Fault A.*/
    _FLTA1IE     = (0x0080 & config) >> 7;

#ifdef _FLTB1IF
    /* clear the Interrupt flags */
    _FLTB1IF = 0;	

    /* Set priority for the Fault B */
    _FLTB1IP    = (0x0700 & config)>>8;

    /* enable /disable of interrupt Fault B.*/
    _FLTB1IE     = (0x0800 & config) >> 11;
#endif

}

#else
#warning "Does not build on this target"
#endif
