#include <pwm12.h>

#ifdef _FLTA2IF

/**********************************************************************
* Function Name     :ConfigIntMCPWM2
* Description       :This function Enable/Disable interrupts and 
*                    sets Interrupt priority for period match, 
*                    FaultA.  
* Parameters        :unsigned int Config
* Return Value      :None 
**********************************************************************/

void ConfigIntMCPWM2(unsigned int config)
{

    /* clear the Interrupt flags */
    _PWM2IF = 0;	
    _FLTA2IF = 0;	

    /* Set priority for the period match */
    _PWM2IP      = (0x0007 & config);

    /* Set priority for the Fault A */
    _FLTA2IP    = (0x0070 & config)>> 4;

    /* enable /disable of interrupt Period match */
    _PWM2IE      = (0x0008 & config) >> 3;

    /* enable /disable of interrupt Fault A.*/
    _FLTA2IE     = (0x0080 & config) >> 7;


}

#else
#warning "Does not build on this target"
#endif
