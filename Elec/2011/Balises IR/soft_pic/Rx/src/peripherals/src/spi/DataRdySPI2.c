/********************************************************************
*     Function Name : DataRdySPI2                                   *
*     Description   : Determine if there is a byte/word to be read  *
*                     from the SPIBUF register.                     *
*     Parameters    : None                                          *
*     Return Value  : status bit to indicate if RBF = 1 else 0      *
********************************************************************/

#include "spi.h"

#if defined(_SPI2IF)

char DataRdySPI2()
{   
    return SPI2STATbits.SPIRBF; /* return RBF bit status */
}

#else
#warning "Does not build on this target"
#endif
