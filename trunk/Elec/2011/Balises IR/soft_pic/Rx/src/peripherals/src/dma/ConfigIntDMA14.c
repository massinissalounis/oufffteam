#include "dma.h"

#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA14IF)

/*********************************************************************
* Function Name     : ConfigIntDMA14
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA14(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS8bits.DMA14IF = 0;
  
    /* Setting Priority */
    IPC33bits.DMA14IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC8bits.DMA14IE = (config & 0x10)>>4;
}
#else
#warning "Does not build on this target"
#endif
