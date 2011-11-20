#include "dma.h"

#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA12IF)

/*********************************************************************
* Function Name     : ConfigIntDMA12
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA12(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS8bits.DMA12IF = 0;
  
    /* Setting Priority */
    IPC32bits.DMA12IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC8bits.DMA12IE = (config & 0x10)>>4;
}

#else
#warning "Does not build on this target"
#endif
