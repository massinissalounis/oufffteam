#include "dma.h"

#ifdef _DMA1IF

/*********************************************************************
* Function Name     : CloseDMA1
* Description       : This function turns off the DMA1 channel. 
*                     Also, the Interrupt enable (DMA1IE) and Interrupt 
*                     flag (DMA1IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA1(void)
{
    /* disable DMA1 interrupt */
    IEC0bits.DMA1IE = 0;

    /* turn off DMA1 */
    DMA1CONbits.CHEN = 0;    

    /* clear DMA1IF bit */
    IFS0bits.DMA1IF = 0;
}

#else
#warning "Does not build on this target"
#endif
