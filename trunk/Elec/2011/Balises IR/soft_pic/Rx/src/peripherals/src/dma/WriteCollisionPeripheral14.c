#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA14IF)

/*********************************************************************
* Function Name     : WriteCollisionPeripheral14
* Description       : This function returns the channel14 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL14 bit status
*********************************************************************/

char WriteCollisionPeripheral14(void)
{
    return(DMAPWCbits.PWCOL14);
}

#else
#warning "Does not build on this target"
#endif
