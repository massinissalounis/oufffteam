#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA14IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA14
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL14 bit status
*********************************************************************/

char RequestCollisionDMA14(void)
{
    return(DMARQCbits.RQCOL14);
}

#else
#warning "Does not build on this target"
#endif
