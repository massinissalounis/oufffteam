#include "dma.h"

#ifdef _DMA3IF

/*********************************************************************
* Function Name     : PingPongStatusDMA3
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST3 bit status
*********************************************************************/

char PingPongStatusDMA3(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPPSbits.PPST3);
#else
    return (DMACS1bits.PPST3);	/* returns the PPST3 bit status */
#endif
}

#else
#warning "Does not build on this target"
#endif
