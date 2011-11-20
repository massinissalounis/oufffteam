#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA12IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA12
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL12 bit status
*********************************************************************/

char RequestCollisionDMA12(void)
{
    return(DMARQCbits.RQCOL12);
}

#else
#warning "Does not build on this target"
#endif
