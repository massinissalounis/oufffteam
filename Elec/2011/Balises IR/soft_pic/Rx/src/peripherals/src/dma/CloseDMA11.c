#include "dma.h"

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_DMA11IF)

/*********************************************************************
* Function Name     : CloseDMA11
* Description       : This function turns off the DMA11 channel. 
*                     Also, the Interrupt enable (DMA11IE) and Interrupt 
*                     flag (DMA11IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA11(void)
{
    /* disable DMA11 interrupt */
    DisableIntDMA11;

    /* turn off DMA11 */
    DMA11CONbits.CHEN = 0;    

    /* clear DMA11IF bit */
    IFS7bits.DMA11IF = 0;
}
#else
#warning "Does not build on this target"
#endif
