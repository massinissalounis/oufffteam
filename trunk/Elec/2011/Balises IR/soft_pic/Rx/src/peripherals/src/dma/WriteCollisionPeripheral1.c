#include "dma.h"

#ifdef _DMA1IF

/*********************************************************************
* Function Name     : WriteCollisionPeripheral1
* Description       : This function returns the channel0 peripheral 
		      write collision flag bit.
* Parameters        : None
* Return Value      : PWCOL1 bit status
*********************************************************************/

char WriteCollisionPeripheral1(void)
{

#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPWCbits.PWCOL1);
#else
    return (DMACS0bits.PWCOL1);	/* returns the PWCOL1 bit status */
#endif
}


#else
#warning "Does not build on this target"
#endif
