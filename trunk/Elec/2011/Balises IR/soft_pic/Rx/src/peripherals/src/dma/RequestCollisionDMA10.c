#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA10IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA10
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL10 bit status
*********************************************************************/

char RequestCollisionDMA10(void)
{
    return(DMARQCbits.RQCOL10);
}

#else
#warning "Does not build on this target"
#endif
