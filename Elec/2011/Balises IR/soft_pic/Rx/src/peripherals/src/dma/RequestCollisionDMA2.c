#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA2IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA2
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL2 bit status
*********************************************************************/

char RequestCollisionDMA2(void)
{
    return(DMARQCbits.RQCOL2);
}

#else
#warning "Does not build on this target"
#endif
