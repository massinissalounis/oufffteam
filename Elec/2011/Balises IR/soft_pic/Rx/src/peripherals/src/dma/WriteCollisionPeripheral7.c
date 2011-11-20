#include "dma.h"

#ifdef _DMA7IF

/*********************************************************************
* Function Name     : WriteCollisionPeripheral7
* Description       : This function returns the channel7 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL7 bit status
*********************************************************************/

char WriteCollisionPeripheral7(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPWCbits.PWCOL7);
#else
    return (DMACS0bits.PWCOL7);	/* returns the PWCOL7 bit status */
#endif
}


#else
#warning "Does not build on this target"
#endif
