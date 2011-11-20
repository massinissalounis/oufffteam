#include "dma.h"

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined(_DMA9IF)
/*********************************************************************
* Function Name     : CloseDMA9
* Description       : This function turns off the DMA9 channel. 
*                     Also, the Interrupt enable (DMA9IE) and Interrupt 
*                     flag (DMA9IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA9(void)
{
    /* disable DMA9 interrupt */
    DisableIntDMA9;

    /* turn off DMA9 */
    DMA9CONbits.CHEN = 0;    

    /* clear DMA9IF bit */
    IFS7bits.DMA9IF = 0;
}
#else
#warning "Does not build on this target"
#endif
