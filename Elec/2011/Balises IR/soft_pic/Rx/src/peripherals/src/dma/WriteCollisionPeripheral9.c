#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA9IF)

/*********************************************************************
* Function Name     : WriteCollisionPeripheral9
* Description       : This function returns the channel9 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL9 bit status
*********************************************************************/

char WriteCollisionPeripheral9(void)
{
    return(DMAPWCbits.PWCOL9);
}

#else
#warning "Does not build on this target"
#endif
