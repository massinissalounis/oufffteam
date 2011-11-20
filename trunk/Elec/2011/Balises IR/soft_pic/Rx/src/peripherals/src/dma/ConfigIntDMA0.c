#include "dma.h"

#ifdef _DMA0IF

/*********************************************************************
* Function Name     : ConfigIntDMA0
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA0(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS0bits.DMA0IF = 0;
  
    /* Setting Priority */
    IPC1bits.DMA0IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC0bits.DMA0IE = (config & 0x10)>>4;
}

#else
#warning "Does not build on this target"
#endif
