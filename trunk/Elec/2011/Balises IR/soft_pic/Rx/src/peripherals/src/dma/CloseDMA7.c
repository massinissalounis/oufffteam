#include "dma.h"

#ifdef _DMA7IF

/*********************************************************************
* Function Name     : CloseDMA7
* Description       : This function turns off the DMA7 channel. 
*                     Also, the Interrupt enable (DMA7IE) and Interrupt 
*                     flag (DMA7IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA7(void)
{
    /* disable DMA7 interrupt */
    IEC4bits.DMA7IE = 0;

    /* turn off DMA7 */
    DMA7CONbits.CHEN = 0;    

	/* clear DMA7IF bit */
    IFS4bits.DMA7IF = 0;
}

#else
#warning "Does not build on this target"
#endif
