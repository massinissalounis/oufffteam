#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA1IF)

/*********************************************************************
* Function Name     : RequestCollisionDMA1
* Description       : This function returns 1 is force and peripheral
*                     request occured simultaneously on this channel.
* Parameters        : None
* Return Value      : RQCOL1 bit status
*********************************************************************/

char RequestCollisionDMA1(void)
{
    return(DMARQCbits.RQCOL1);
}

#else
#warning "Does not build on this target"
#endif
