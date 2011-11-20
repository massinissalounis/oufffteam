#include "dma.h"

#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA9IF)

/*********************************************************************
* Function Name     : ConfigIntDMA9
* Description       : This function configures DMA Interrupt.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigIntDMA9(unsigned int config)
{
    /* Clearing the Interrupt Flag bit */
    IFS7bits.DMA9IF = 0;
  
    /* Setting Priority */
    IPC29bits.DMA9IP = config & 0x07;
  
    /* Setting the Interrupt enable bit */
    IEC7bits.DMA9IE = (config & 0x10)>>4;
}
#else
#warning "Does not build on this target"
#endif
