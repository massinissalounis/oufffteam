#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA9IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA9
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL9 bit status
*********************************************************************/

char RequestCollisionDMA9(void)
{
    return(DMARQCbits.RQCOL9);
}

#else
#warning "Does not build on this target"
#endif
