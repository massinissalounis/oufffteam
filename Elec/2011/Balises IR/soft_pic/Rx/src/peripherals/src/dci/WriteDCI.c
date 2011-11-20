#include "dci.h"

#ifdef _DCIIF

/*********************************************************************
*    Function Name : WriteDCI
*    Description   : This routine writes the data_out value  to one
*                    of the transmit buffer locations given by buffer
*    Parameters    : unsigned char : buffer
*		     unsigned int  : data_out
*    Return Value  : None
*********************************************************************/

void WriteDCI(unsigned int data_out, unsigned char buffer)
{
     (*(&TXBUF0+ (buffer&3))) = data_out;
}

#else
#warning "Does not build on this target"
#endif
