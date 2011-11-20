#include "dma.h"

#ifdef _DMA0IF

/*********************************************************************
* Function Name     : LastDMAActive()
* Description       : This function returns the channel number from which 
		    : last data was transferred.
*             
* Parameters        : None
* Return Value      : char channel number
*********************************************************************/

char LastDMAActive(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
 	return(DMALCAbits.LSTCH); 
#else
 	return(DMACS1bits.LSTCH); 
#endif
					
}

#else
#warning "Does not build on this target"
#endif
