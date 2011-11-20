#include "adc12.h"

#ifdef _ADC_12BIT

/*********************************************************************
* Function Name     : ConfigIntADC12
* Description       : This function configures ADC Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntADC12(unsigned int config)
{
    /* clearing the Interrupt Flag bit */
    IFS0bits.ADIF = 0;

    /* Setting Priority */
    IPC2bits.ADIP = config & 0x07;

    /* configuring the Interrupt enable bit */
    IEC0bits.ADIE = (config & 0x08)>>3;
}

#else
#warning "Does not build on this target"
#endif
