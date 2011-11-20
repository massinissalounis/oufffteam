#include "dma.h"

#if (defined(__dsPIC33E__) || defined (__PIC24E__)) && defined (_DMA11IF)

/*********************************************************************
* Function Name     : DMA11PingPongStatus
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST11 bit status
*********************************************************************/

char PingPongStatusDMA11(void)
{
    return(DMAPPSbits.PPST11);
}

#else
#warning "Does not build on this target"
#endif
