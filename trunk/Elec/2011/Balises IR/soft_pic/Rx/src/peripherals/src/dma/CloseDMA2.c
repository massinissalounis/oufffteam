#include "dma.h"

#ifdef _DMA2IF

/*********************************************************************
* Function Name     : CloseDMA2
* Description       : This function turns off the DMA2 channel. 
*                     Also, the Interrupt enable (DMA2IE) and Interrupt 
*                     flag (DMA2IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA2(void)
{
    /* disable DMA2 interrupt */
    IEC1bits.DMA2IE = 0;

    /* turn off DMA2 */
    DMA2CONbits.CHEN = 0;    

	/* clear DMA2IF bit */
    IFS1bits.DMA2IF = 0;
}

#else
#warning "Does not build on this target"
#endif
