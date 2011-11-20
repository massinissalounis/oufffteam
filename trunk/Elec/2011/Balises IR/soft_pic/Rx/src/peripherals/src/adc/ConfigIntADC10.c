#include "adc10.h"

#ifdef _ADC_10BIT

/*********************************************************************
* Function Name     : ConfigIntADC10
* Description       : This function configures ADC Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntADC10(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS0bits.ADIF = 0;
  
    /* Setting Priority */
    IPC2bits.ADIP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC0bits.ADIE = (config & 0x08)>>3;
}

#else
#warning "Does not build on this target"
#endif
