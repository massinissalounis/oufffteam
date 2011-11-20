#include "dma.h"

#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA10IF)

/*********************************************************************
* Function Name     : ConfigIntDMA10
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA10(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS7bits.DMA10IF = 0;
  
    /* Setting Priority */
    IPC30bits.DMA10IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC7bits.DMA10IE = (config & 0x10)>>4;
}

#else
#warning "Does not build on this target"
#endif
