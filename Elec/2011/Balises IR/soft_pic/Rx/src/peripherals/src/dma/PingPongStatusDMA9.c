#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA9IF)

/*********************************************************************
* Function Name     : DMA9PingPongStatus
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST9 bit status
*********************************************************************/

char PingPongStatusDMA9(void)
{
    return(DMAPPSbits.PPST9);
}

#else
#warning "Does not build on this target"
#endif
