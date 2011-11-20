#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA4IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA4
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL4 bit status
*********************************************************************/

char RequestCollisionDMA4(void)
{
    return(DMARQCbits.RQCOL4);
}

#else
#warning "Does not build on this target"
#endif
