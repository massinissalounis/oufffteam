#include "dma.h"

#ifdef _DMA4IF

#if defined (__dsPIC33E__) || defined (__PIC24E__)

#warning "Does not build on this target"

#else
/*********************************************************************
* Function Name     : WriteCollisionDMA3
* Description       : This function returns the channel 3 DMA RAM write
		      collision detect.
* Parameters        : None
* Return Value      : XWCOL3 bit status
*********************************************************************/

char WriteCollisionDMA4(void)
{
    return (DMACS0bits.XWCOL4);	/* returns the XWCOL3 bit status */
}

#endif
#endif
