#include "dma.h"

#ifdef _DMA2IF

/*********************************************************************
* Function Name     : ConfigIntDMA2
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA2(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS1bits.DMA2IF = 0;
  
    /* Setting Priority */
    IPC6bits.DMA2IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC1bits.DMA2IE = (config & 0x10) >> 4;
}

#else
#warning "Does not build on this target"
#endif
