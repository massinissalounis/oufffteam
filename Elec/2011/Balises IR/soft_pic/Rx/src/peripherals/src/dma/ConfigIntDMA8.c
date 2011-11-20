#include "dma.h"

#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA8IF)

/*********************************************************************
* Function Name     : ConfigIntDMA8
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA8(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS7bits.DMA8IF = 0;
  
    /* Setting Priority */
    IPC29bits.DMA8IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC7bits.DMA8IE = (config & 0x10)>>4;
}
#else
#warning "Does not build on this target"
#endif
