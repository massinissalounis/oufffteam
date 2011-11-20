#include "dma.h"

#ifdef _DMA0IF

#if defined (__dsPIC33E__) || defined (__PIC24E__)

#warning "Does not build on this target"

#else
/*********************************************************************
* Function Name     : WriteCollisionDMA0
* Description       : This function returns the channel 0 DMA RAM write
		      collision detect.
* Parameters        : None
* Return Value      : XWCOL0 bit status
*********************************************************************/

char WriteCollisionDMA0(void)
{
    return (DMACS0bits.XWCOL0);	/* returns the XWCOL0 bit status */
}

#endif
#endif
