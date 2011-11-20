#include "dma.h"

#ifdef _DMA3IF

/*********************************************************************
* Function Name     : CloseDMA3
* Description       : This function turns off the DMA3 channel. 
*                     Also, the Interrupt enable (DMA3IE) and Interrupt 
*                     flag (DMA3IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA3(void)
{
    /* disable DMA3 interrupt */
    IEC2bits.DMA3IE = 0;

    /* turn off DMA3 */
    DMA3CONbits.CHEN = 0;    

	/* clear DMA3IF bit */
    IFS2bits.DMA3IF = 0;
}

#else
#warning "Does not build on this target"
#endif
