/********************************************************************
*     Function Name : WriteSPI2                                     *
*     Description   : This routine writes a single byte/word to     * 
*                     the SPI bus.                                  *
*     Parameters    : Single data byte/word for SPI bus             *
*     Return Value  : None                                          *
********************************************************************/

#include "spi.h"

#if defined(_SPI2IF)

#if defined(_SPI_V2)
void WriteSPI2(unsigned int data_out)
{   
    if (SPI2CON1bits.MODE16)           /* word write */
        SPI2BUF = data_out;
    else 
        SPI2BUF = data_out & 0xff;	  /*  byte write  */
}
#elif defined(_SPI_V1)
void WriteSPI2(unsigned int data_out)
{   
    if (SPI2CONbits.MODE16)           /* word write */
        SPI2BUF = data_out;
    else 
        SPI2BUF = data_out & 0xff;	  /*  byte write  */
}
#endif

#else
#warning "Does not build on this target"
#endif
