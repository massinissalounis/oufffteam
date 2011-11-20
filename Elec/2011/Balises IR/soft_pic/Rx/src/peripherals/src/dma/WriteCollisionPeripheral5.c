#include "dma.h"

#ifdef _DMA5IF

/*********************************************************************
* Function Name     : WriteCollisionPeripheral5
* Description       : This function returns the channel5 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL5 bit status
*********************************************************************/

char WriteCollisionPeripheral5(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPWCbits.PWCOL5);
#else
    return (DMACS0bits.PWCOL5);	/* returns the PWCOL5 bit status */
#endif
}


#else
#warning "Does not build on this target"
#endif
