#include "dma.h"

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_DMA13IF)

/*********************************************************************
* Function Name     : CloseDMA13
* Description       : This function turns off the DMA13 channel. 
*                     Also, the Interrupt enable (DMA13IE) and Interrupt 
*                     flag (DMA13IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA13(void)
{
    /* disable DMA13 interrupt */
    DisableIntDMA13;

    /* turn off DMA13 */
    DMA13CONbits.CHEN = 0;    

    /* clear DMA13IF bit */
    IFS8bits.DMA13IF = 0;
}
#else
#warning "Does not build on this target"
#endif
