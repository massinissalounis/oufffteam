#include "dma.h"

#ifdef _DMA0IF

/*********************************************************************
* Function Name     : CloseDMA0
* Description       : This function turns off the DMA0 channel. 
*                     Also, the Interrupt enable (DMA0IE) and Interrupt 
*                     flag (DMA0IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA0(void)
{
    /* disable DMA0 interrupt */
    IEC0bits.DMA0IE = 0;

    /* turn off DMA0 */
    DMA0CONbits.CHEN = 0;    

    /* clear DMA0IF bit */
    IFS0bits.DMA0IF = 0;
}

#else
#warning "Does not build on this target"
#endif
