#include "dma.h"

#ifdef _DMA6IF

/*********************************************************************
* Function Name     : CloseDMA6
* Description       : This function turns off the DMA6 channel. 
*                     Also, the Interrupt enable (DMA6IE) and Interrupt 
*                     flag (DMA6IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA6(void)
{
    /* disable DMA6 interrupt */
    IEC4bits.DMA6IE = 0;

    /* turn off DMA6 */
    DMA6CONbits.CHEN = 0;    

	/* clear DMA6IF bit */
    IFS4bits.DMA6IF = 0;
}

#else
#warning "Does not build on this target"
#endif
