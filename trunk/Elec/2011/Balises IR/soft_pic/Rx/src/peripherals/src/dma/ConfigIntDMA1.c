#include "dma.h"

#ifdef _DMA1IF

/*********************************************************************
* Function Name     : ConfigIntDMA1
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA1(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS0bits.DMA1IF = 0;
  
    /* Setting Priority */
    IPC3bits.DMA1IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC0bits.DMA1IE = (config & 0x10) >> 4;
}

#else
#warning "Does not build on this target"
#endif
