#include "dma.h"

#ifdef _DMA6IF

/*********************************************************************
* Function Name     : ConfigIntDMA6
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA6(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS4bits.DMA6IF = 0;
  
    /* Setting Priority */
    IPC17bits.DMA6IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC4bits.DMA6IE = (config & 0x10)>>4;
}

#else
#warning "Does not build on this target"
#endif
