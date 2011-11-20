#include "dma.h"

#ifdef _DMA4IF

/*********************************************************************
* Function Name     : CloseDMA4
* Description       : This function turns off the DMA4 channel. 
*                     Also, the Interrupt enable (DMA4IE) and Interrupt 
*                     flag (DMA4IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA4(void)
{
    /* disable DMA4 interrupt */
    IEC2bits.DMA4IE = 0;

    /* turn off DMA4 */
    DMA4CONbits.CHEN = 0;    

	/* clear DMA4IF bit */
    IFS2bits.DMA4IF = 0;
}

#else
#warning "Does not build on this target"
#endif
