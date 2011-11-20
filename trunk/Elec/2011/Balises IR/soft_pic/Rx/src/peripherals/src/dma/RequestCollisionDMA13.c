#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA13IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA13
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL13 bit status
*********************************************************************/

char RequestCollisionDMA13(void)
{
    return(DMARQCbits.RQCOL13);
}

#else
#warning "Does not build on this target"
#endif
