#include "dma.h"

#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA11IF)

/*********************************************************************
* Function Name     : ConfigIntDMA11
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA11(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS7bits.DMA11IF = 0;
  
    /* Setting Priority */
    IPC30bits.DMA11IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC7bits.DMA11IE = (config & 0x10)>>4;
}
#else
#warning "Does not build on this target"
#endif
