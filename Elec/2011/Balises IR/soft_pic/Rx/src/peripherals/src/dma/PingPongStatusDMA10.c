#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA10IF)

/*********************************************************************
* Function Name     : DMA10PingPongStatus
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST10 bit status
*********************************************************************/

char PingPongStatusDMA10(void)
{
    return(DMAPPSbits.PPST10);
}

#else
#warning "Does not build on this target"
#endif
