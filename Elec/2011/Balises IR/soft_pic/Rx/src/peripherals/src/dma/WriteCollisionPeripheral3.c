#include "dma.h"

#ifdef _DMA3IF

/*********************************************************************
* Function Name     : WriteCollisionPeripheral3
* Description       : This function returns the channel3 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL3 bit status
*********************************************************************/

char WriteCollisionPeripheral3(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPWCbits.PWCOL3);
#else
    return (DMACS0bits.PWCOL3);	/* returns the PWCOL3 bit status */
#endif
}


#else
#warning "Does not build on this target"
#endif
