#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA14IF)

/*********************************************************************
* Function Name     : DMA14PingPongStatus
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST14 bit status
*********************************************************************/

char PingPongStatusDMA14(void)
{
    return(DMAPPSbits.PPST14);
}

#else
#warning "Does not build on this target"
#endif
