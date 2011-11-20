#include "dma.h"

#ifdef _DMA1IF

#if defined (__dsPIC33E__) || defined (__PIC24E__)

#warning "Does not build on this target"

#else
/*********************************************************************
* Function Name     : WriteCollisionDMA1
* Description       : This function returns the channel 1 DMA RAM write
		      collision detect.
* Parameters        : None
* Return Value      : XWCOL1 bit status
*********************************************************************/

char WriteCollisionDMA1(void)
{
    return (DMACS0bits.XWCOL1);	/* returns the XWCOL1 bit status */
}

#endif
#endif
