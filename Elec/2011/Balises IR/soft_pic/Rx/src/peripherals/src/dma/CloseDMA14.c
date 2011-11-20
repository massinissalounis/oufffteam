#include "dma.h"

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_DMA14IF)

/*********************************************************************
* Function Name     : CloseDMA14
* Description       : This function turns off the DMA14 channel. 
*                     Also, the Interrupt enable (DMA14IE) and Interrupt 
*                     flag (DMA14IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA14(void)
{
    /* disable DMA14 interrupt */
    DisableIntDMA14;

    /* turn off DMA14 */
    DMA14CONbits.CHEN = 0;    

    /* clear DMA14IF bit */
    IFS8bits.DMA14IF = 0;
}
#else
#warning "Does not build on this target"
#endif
