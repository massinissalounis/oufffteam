#include "dma.h"

#ifdef _DMA1IF

/*********************************************************************
* Function Name     : PingPongStatusDMA0
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST1 bit status
*********************************************************************/

char PingPongStatusDMA1(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPPSbits.PPST1);
#else
    return (DMACS1bits.PPST1);	/* returns the PPST1 bit status */
#endif
}

#else
#warning "Does not build on this target"
#endif
