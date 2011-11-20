#include "dci.h"

#ifdef _DCIIF

/*********************************************************************
*    Function Name : ReadDCI
*    Description   : This routine returns the data stored in one of
*		     the receive buffers based on the buffer number
*    Return Value  : unsigned int buffer content
*    Parameters    : unsigned char: buffer
*
*********************************************************************/

unsigned int ReadDCI(unsigned char buffer )
{
     return (*(&RXBUF0+ (buffer&0x3)));
}

#else
#warning "Does not build on this target"
#endif
