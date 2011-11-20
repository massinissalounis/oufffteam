#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA13IF)

/*********************************************************************
* Function Name     : DMA13PingPongStatus
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST13 bit status
*********************************************************************/

char PingPongStatusDMA13(void)
{
    return(DMAPPSbits.PPST13);
}

#else
#warning "Does not build on this target"
#endif
