#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA10IF)

/*********************************************************************
* Function Name     : WriteCollisionPeripheral10
* Description       : This function returns the channel10 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL10 bit status
*********************************************************************/

char WriteCollisionPeripheral10(void)
{
    return(DMAPWCbits.PWCOL10);
}

#else
#warning "Does not build on this target"
#endif
