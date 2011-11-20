#include "dma.h"

#if (defined (__PIC24E__) || defined (__dsPIC33E__)) && defined (_DMA10IF)

/*********************************************************************
* Function Name     : CloseDMA10
* Description       : This function turns off the DMA10 channel. 
*                     Also, the Interrupt enable (DMA10IE) and Interrupt 
*                     flag (DMA10IF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDMA10(void)
{
    /* disable DMA10 interrupt */
    DisableIntDMA10;

    /* turn off DMA10 */
    DMA10CONbits.CHEN = 0;    

    /* clear DMA10IF bit */
    IFS7bits.DMA10IF = 0;
}
#else
#warning "Does not build on this target"
#endif
