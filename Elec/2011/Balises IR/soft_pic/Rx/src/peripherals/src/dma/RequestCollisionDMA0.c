#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA0IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA0
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL0 bit status
*********************************************************************/

char RequestCollisionDMA0(void)
{
    return(DMARQCbits.RQCOL0);
}

#else
#warning "Does not build on this target"
#endif
