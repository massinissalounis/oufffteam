#include <adc.h>

#ifdef _AD1IF

/*********************************************************************
* Function Name     : ConfigIntADC1
* Description       : This function configures ADC Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntADC1(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS0bits.AD1IF = 0;
  
    /* Setting Priority */
    IPC3bits.AD1IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC0bits.AD1IE = (config & 0x08)>>3;
}

#else
#warning "Does not build on this target"
#endif
