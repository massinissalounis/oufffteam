#include "dma.h"

#ifdef _DMA0IF

/*********************************************************************
* Function Name     : DMARAMAddress
* Description       : This function returns the recent DMA RAM address
			          accessed by DMA controller bits.
* Parameters        : None
* Return Value      : unsigned int
*********************************************************************/
#if defined(__dsPIC33E__) || defined (__PIC24E__)
unsigned long int DMARAMAddress(void)
{
    unsigned long int address;

    address = (unsigned long int)DSADRH << 16;
    address |= DSADRL;

    return(address); 
}
#else
unsigned int DMARAMAddress(void)
{
    return (DSADR);	/* returns the DSADR register contents */
}
#endif
#else
#warning "Does not build on this target"
#endif
