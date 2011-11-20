#include "dma.h"

#ifdef _DMA7IF

/*********************************************************************
* Function Name     : PingPongStatusDMA7
* Description       : This function returns which register is selected
			for ping pong.
* Parameters        : None
* Return Value      : PPST7 bit status
*********************************************************************/

char PingPongStatusDMA7(void)
{
#if defined(__dsPIC33E__) || defined (__PIC24E__)
    return(DMAPPSbits.PPST7);
#else
    return (DMACS1bits.PPST7);	/* returns the PPST7 bit status */
#endif
}

#else
#warning "Does not build on this target"
#endif
