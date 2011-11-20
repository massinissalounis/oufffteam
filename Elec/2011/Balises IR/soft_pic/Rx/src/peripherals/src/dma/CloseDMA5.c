#include "dma.h"

#ifdef _DMA5IF

/*********************************************************************
* Function Name     : CloseDMA5
* Description       : This function turns off the DMA5 channel. 
*                     Also, the Interrupt enable (DMA5IE) and Interrupt 
*                     flag (DMA5IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA5(void)
{
    /* disable DMA5 interrupt */
    IEC3bits.DMA5IE = 0;

    /* turn off DMA5 */
    DMA5CONbits.CHEN = 0;    

	/* clear DMA5IF bit */
    IFS3bits.DMA5IF = 0;
}

#else
#warning "Does not build on this target"
#endif
