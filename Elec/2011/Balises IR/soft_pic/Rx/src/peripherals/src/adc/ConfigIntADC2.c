#include <adc.h>

#ifdef _AD2IF

/*********************************************************************
* Function Name     : ConfigIntADC2
* Description       : This function configures ADC Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntADC2(unsigned int config)
{
    /* clearing the Interrupt Flag bit */
    IFS1bits.AD2IF = 0;

    /* Setting Priority */
    IPC5bits.AD2IP = config & 0x07;

    /* configuring the Interrupt enable bit */
    IEC1bits.AD2IE = (config & 0x08)>>3;
}

#else
#warning "Does not build on this target"
#endif
