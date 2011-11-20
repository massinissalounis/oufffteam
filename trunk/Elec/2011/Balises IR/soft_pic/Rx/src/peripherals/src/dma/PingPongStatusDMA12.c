#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA12IF)

/*********************************************************************
* Function Name     : DMA12PingPongStatus
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST12 bit status
*********************************************************************/

char PingPongStatusDMA12(void)
{
    return(DMAPPSbits.PPST12);
}

#else
#warning "Does not build on this target"
#endif
