#include "dma.h"

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined(_DMA12IF)

/*********************************************************************
* Function Name     : CloseDMA12
* Description       : This function turns off the DMA12 channel. 
*                     Also, the Interrupt enable (DMA12IE) and Interrupt 
*                     flag (DMA12IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA12(void)
{
    /* disable DMA12 interrupt */
    DisableIntDMA12;

    /* turn off DMA12 */
    DMA12CONbits.CHEN = 0;    

    /* clear DMA12IF bit */
    IFS8bits.DMA12IF = 0;
}

#else
#warning "Does not build on this target"
#endif
