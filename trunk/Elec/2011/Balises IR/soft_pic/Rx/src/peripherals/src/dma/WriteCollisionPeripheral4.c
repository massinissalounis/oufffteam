#include "dma.h"

#ifdef _DMA4IF

/*********************************************************************
* Function Name     : WriteCollisionPeripheral4
* Description       : This function returns the channel4 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL4 bit status
*********************************************************************/

char WriteCollisionPeripheral4(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPWCbits.PWCOL4);
#else
    return (DMACS0bits.PWCOL4);	/* returns the PWCOL4 bit status */
#endif
}


#else
#warning "Does not build on this target"
#endif
