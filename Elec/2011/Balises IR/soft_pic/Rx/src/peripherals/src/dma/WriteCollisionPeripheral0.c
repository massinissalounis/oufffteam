#include "dma.h"

#ifdef _DMA0IF

/*********************************************************************
* Function Name     : WriteCollisionDMA0
* Description       : This function returns the channel0 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL0 bit status
*********************************************************************/

char WriteCollisionPeripheral0(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPWCbits.PWCOL0);
#else
    return (DMACS0bits.PWCOL0);	/* returns the PWCOL0 bit status */
#endif
}

#else
#warning "Does not build on this target"
#endif
