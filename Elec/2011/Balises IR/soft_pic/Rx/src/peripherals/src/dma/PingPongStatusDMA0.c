#include "dma.h"

#ifdef _DMA0IF

/*********************************************************************
* Function Name     : DMA0PingPongStatus
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST0 bit status
*********************************************************************/

char PingPongStatusDMA0(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPPSbits.PPST0);
#else
    return (DMACS1bits.PPST0);	/* returns the PPST0 bit status */
#endif
}

#else
#warning "Does not build on this target"
#endif
