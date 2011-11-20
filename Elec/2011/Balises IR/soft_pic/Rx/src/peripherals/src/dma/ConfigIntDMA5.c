#include "dma.h"

#ifdef _DMA5IF

/*********************************************************************
* Function Name     : ConfigIntDMA5
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA5(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS3bits.DMA5IF = 0;
  
    /* Setting Priority */
    IPC15bits.DMA5IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC3bits.DMA5IE = (config & 0x10) >> 4;
}

#else
#warning "Does not build on this target"
#endif
