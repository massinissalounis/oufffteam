#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA8IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA8
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL8 bit status
*********************************************************************/

char RequestCollisionDMA8(void)
{
    return(DMARQCbits.RQCOL8);
}

#else
#warning "Does not build on this target"
#endif
