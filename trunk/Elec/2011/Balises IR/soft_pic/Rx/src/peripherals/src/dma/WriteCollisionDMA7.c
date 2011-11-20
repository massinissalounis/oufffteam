#include "dma.h"

#ifdef _DMA7IF

#if defined (__dsPIC33E__) || defined (__PIC24E__)

#warning "Does not build on this target"

#else
/*********************************************************************
* Function Name     : WriteCollisionDMA7
* Description       : This function returns the channel 7 DMA RAM write
		      collision detect.
* Parameters        : None
* Return Value      : XWCOL7 bit status
*********************************************************************/

char WriteCollisionDMA7(void)
{
    return (DMACS0bits.XWCOL7);	/* returns the XWCOL7 bit status */
}

#endif
#endif
