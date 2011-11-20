#include "dci.h"

#ifdef _DCIIF

/***********************************************************************
*    Function Name : BufferEmptyDCI				
*    Description   : This routine determines if transmit buffer is empty	
*                    by returning the TMPTY bit ofDCISTAT register.
*    Parameters    : None
*    Return Value  : char: TMPTY bit status
************************************************************************/

char BufferEmptyDCI(void)
{
     return DCISTATbits.TMPTY; 	/* returns the TMPTY bit status */
}

#else
#warning "Does not build on this target"
#endif
