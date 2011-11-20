#include "dci.h"

#ifdef _DCIIF

/*********************************************************************
*    Function Name : DataRdyDCI
*    Description   : This routine Checks if data is available in the
*                    receive buffers by returning the RFUL bit.
*    Parameters    : None
*    Return Value  : char: RFUL bit status
*********************************************************************/

char DataRdyDCI(void)
{
     return DCISTATbits.RFUL;   /* returns the RFUL bit status */
}

#else
#warning "Does not build on this target"
#endif
