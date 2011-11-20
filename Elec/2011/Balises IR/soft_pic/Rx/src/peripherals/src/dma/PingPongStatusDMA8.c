#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA8IF)

/*********************************************************************
* Function Name     : DMA8PingPongStatus
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST8 bit status
*********************************************************************/

char PingPongStatusDMA8(void)
{
    return(DMAPPSbits.PPST8);
}

#else
#warning "Does not build on this target"
#endif
