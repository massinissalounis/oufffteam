#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA11IF)

/*********************************************************************
* Function Name     : WriteCollisionPeripheral11
* Description       : This function returns the channel11 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL11 bit status
*********************************************************************/

char WriteCollisionPeripheral11(void)
{
    return(DMAPWCbits.PWCOL11);
}

#else
#warning "Does not build on this target"
#endif
