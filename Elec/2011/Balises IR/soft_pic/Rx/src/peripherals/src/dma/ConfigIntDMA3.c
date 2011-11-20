#include "dma.h"

#ifdef _DMA3IF

/*********************************************************************
* Function Name     : ConfigIntDMA3
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA3(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS2bits.DMA3IF = 0;
  
    /* Setting Priority */
    IPC9bits.DMA3IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC2bits.DMA3IE = (config & 0x10)>>4;
}

#else
#warning "Does not build on this target"
#endif
