#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA11IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA11
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL11 bit status
*********************************************************************/

char RequestCollisionDMA11(void)
{
    return(DMARQCbits.RQCOL11);
}

#else
#warning "Does not build on this target"
#endif
