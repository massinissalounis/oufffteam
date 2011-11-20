#include "dma.h"

#ifdef _DMA2IF

/*********************************************************************
* Function Name     : WriteCollisionPeripheral2
* Description       : This function returns the channel2 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL2 bit status
*********************************************************************/

char WriteCollisionPeripheral2(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPWCbits.PWCOL2);
#else
    return (DMACS0bits.PWCOL2);	/* returns the PWCOL2 bit status */
#endif
}


#else
#warning "Does not build on this target"
#endif
