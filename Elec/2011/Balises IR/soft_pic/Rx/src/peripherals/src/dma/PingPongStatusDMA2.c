#include "dma.h"

#ifdef _DMA2IF

/*********************************************************************
* Function Name     : PingPongStatusDMA2
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST2 bit status
*********************************************************************/

char PingPongStatusDMA2(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPPSbits.PPST2);
#else
    return (DMACS1bits.PPST2);	/* returns the PPST2 bit status */
#endif
}

#else
#warning "Does not build on this target"
#endif
