#include "dma.h"

#ifdef _DMA6IF

/*********************************************************************
* Function Name     : WriteCollisionPeripheral6
* Description       : This function returns the channel6 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL6 bit status
*********************************************************************/

char WriteCollisionPeripheral6(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return (DMAPWCbits.PWCOL6);
#else
    return (DMACS0bits.PWCOL6);	/* returns the PWCOL6 bit status */
#endif
}


#else
#warning "Does not build on this target"
#endif
