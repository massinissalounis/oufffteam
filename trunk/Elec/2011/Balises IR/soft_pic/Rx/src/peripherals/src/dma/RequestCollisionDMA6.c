#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA6IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA6
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL6 bit status
*********************************************************************/

char RequestCollisionDMA6(void)
{
    return(DMARQCbits.RQCOL6);
}

#else
#warning "Does not build on this target"
#endif
