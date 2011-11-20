#include "dma.h"

#ifdef _DMA4IF

/*********************************************************************
* Function Name     : ConfigIntDMA4
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA4(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS2bits.DMA4IF = 0;
  
    /* Setting Priority */
    IPC11bits.DMA4IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC2bits.DMA4IE = (config & 0x10) >> 4;
}

#else
#warning "Does not build on this target"
#endif
