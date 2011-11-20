#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA12IF)

/*********************************************************************
* Function Name     : WriteCollisionPeripheral12
* Description       : This function returns the channel12 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL12 bit status
*********************************************************************/

char WriteCollisionPeripheral12(void)
{
    return(DMAPWCbits.PWCOL12);
}

#else
#warning "Does not build on this target"
#endif
