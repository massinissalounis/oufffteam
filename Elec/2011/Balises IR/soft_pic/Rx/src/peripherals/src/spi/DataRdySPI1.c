#include "spi.h"

/********************************************************************
*     Function Name : DataRdySPI1                                   *
*     Description   : Determine if there is a byte/word to be read  *
*                     from the SPIBUF register.                     *
*     Parameters    : None                                          *
*     Return Value  : status bit to indicate if RBF = 1 else 0      *
********************************************************************/

char DataRdySPI1()
{   
    return SPI1STATbits.SPIRBF; /* return the RBF bit status */
}
