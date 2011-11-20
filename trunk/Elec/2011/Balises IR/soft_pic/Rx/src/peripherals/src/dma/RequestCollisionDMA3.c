#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA3IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA3
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL3 bit status
*********************************************************************/

char RequestCollisionDMA3(void)
{
    return(DMARQCbits.RQCOL3);
}

#else
#warning "Does not build on this target"
#endif
