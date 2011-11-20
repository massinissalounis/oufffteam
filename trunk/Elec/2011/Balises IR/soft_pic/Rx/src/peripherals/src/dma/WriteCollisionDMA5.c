#include "dma.h"

#ifdef _DMA5IF

#if defined (__dsPIC33E__) || defined (__PIC24E__)

#warning "Does not build on this target"

#else
/*********************************************************************
* Function Name     : WriteCollisionDMA5
* Description       : This function returns the channel 5 DMA RAM write
		      collision detect.
* Parameters        : None
* Return Value      : XWCOL5 bit status
*********************************************************************/

char WriteCollisionDMA5(void)
{
    return (DMACS0bits.XWCOL5);	/* returns the XWCOL5 bit status */
}

#endif
#endif
