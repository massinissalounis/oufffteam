#include "dma.h"

#ifdef _DMA6IF

/*********************************************************************
* Function Name     : PingPongStatusDMA6
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST6 bit status
*********************************************************************/

char PingPongStatusDMA6(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPPSbits.PPST6);
#else
    return (DMACS1bits.PPST6);	/* returns the PPST6 bit status */
#endif
}

#else
#warning "Does not build on this target"
#endif
