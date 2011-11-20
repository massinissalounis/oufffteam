#include "dma.h"

#ifdef _DMA5IF

/*********************************************************************
* Function Name     : PingPongStatusDMA5
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST5 bit status
*********************************************************************/

char PingPongStatusDMA5(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPPSbits.PPST5);
#else
    return (DMACS1bits.PPST5);	/* returns the PPST5 bit status */
#endif
}

#else
#warning "Does not build on this target"
#endif
