#include "dma.h"

#ifdef _DMA6IF

#if defined (__dsPIC33E__) || defined (__PIC24E__)

#warning "Does not build on this target"

#else
/*********************************************************************
* Function Name     : WriteCollisionDMA6
* Description       : This function returns the channel 6 DMA RAM write
		      collision detect.
* Parameters        : None
* Return Value      : XWCOL6 bit status
*********************************************************************/

char WriteCollisionDMA6(void)
{
    return (DMACS0bits.XWCOL6);	/* returns the XWCOL6 bit status */
}

#endif
#endif
