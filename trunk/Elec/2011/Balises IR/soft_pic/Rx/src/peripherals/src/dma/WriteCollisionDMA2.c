#include "dma.h"

#ifdef _DMA2IF

#if defined (__dsPIC33E__) || defined (__PIC24E__)

#warning "Does not build on this target"

#else
/*********************************************************************
* Function Name     : WriteCollisionDMA2
* Description       : This function returns the channel 2 DMA RAM write
		      collision detect.
* Parameters        : None
* Return Value      : XWCOL2 bit status
*********************************************************************/

char WriteCollisionDMA2(void)
{
    return (DMACS0bits.XWCOL2);	/* returns the XWCOL2 bit status */
}

#endif
#endif
