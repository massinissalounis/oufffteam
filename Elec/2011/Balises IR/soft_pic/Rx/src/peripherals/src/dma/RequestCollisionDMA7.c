#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA7IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA7
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL7 bit status
*********************************************************************/

char RequestCollisionDMA7(void)
{
    return(DMARQCbits.RQCOL7);
}

#else
#warning "Does not build on this target"
#endif
