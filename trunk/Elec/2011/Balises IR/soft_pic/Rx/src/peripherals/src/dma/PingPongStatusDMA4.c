#include "dma.h"

#ifdef _DMA4IF

/*********************************************************************
* Function Name     : PingPongStatusDMA4
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST4 bit status
*********************************************************************/

char PingPongStatusDMA4(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPPSbits.PPST4);
#else
    return (DMACS1bits.PPST4);	/* returns the PPST4 bit status */
#endif
}

#else
#warning "Does not build on this target"
#endif
