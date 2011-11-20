#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA8IF)

/*********************************************************************
* Function Name     : WriteCollisionPeripheral8
* Description       : This function returns the channel8 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL8 bit status
*********************************************************************/

char WriteCollisionPeripheral8(void)
{
    return(DMAPWCbits.PWCOL8);
}

#else
#warning "Does not build on this target"
#endif
