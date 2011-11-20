#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA5IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA5
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL5 bit status
*********************************************************************/

char RequestCollisionDMA5(void)
{
    return(DMARQCbits.RQCOL5);
}

#else
#warning "Does not build on this target"
#endif
