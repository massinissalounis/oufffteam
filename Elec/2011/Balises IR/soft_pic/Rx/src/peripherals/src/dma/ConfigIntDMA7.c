#include "dma.h"

#ifdef _DMA7IF

/*********************************************************************
* Function Name     : ConfigIntDMA7
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA7(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS4bits.DMA7IF = 0;
  
    /* Setting Priority */
    IPC17bits.DMA7IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC4bits.DMA7IE = (config & 0x10) >> 4;
}

#else
#warning "Does not build on this target"
#endif
