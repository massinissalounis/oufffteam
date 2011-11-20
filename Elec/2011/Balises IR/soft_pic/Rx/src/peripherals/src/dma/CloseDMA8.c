#include "dma.h"

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_DMA8IF)

/*********************************************************************
* Function Name     : CloseDMA8
* Description       : This function turns off the DMA8 channel. 
*                     Also, the Interrupt enable (DMA8IE) and Interrupt 
*                     flag (DMA8IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA8(void)
{
    /* disable DMA8 interrupt */
    DisableIntDMA8;

    /* turn off DMA8 */
    DMA8CONbits.CHEN = 0;    

    /* clear DMA8IF bit */
    IFS7bits.DMA8IF = 0;
}
#else
#warning "Does not build on this target"
#endif
