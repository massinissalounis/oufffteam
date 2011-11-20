#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA13IF)

/*********************************************************************
* Function Name     : WriteCollisionPeripheral13
* Description       : This function returns the channel13 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL13 bit status
*********************************************************************/

char WriteCollisionPeripheral13(void)
{
    return(DMAPWCbits.PWCOL13);
}

#else
#warning "Does not build on this target"
#endif
