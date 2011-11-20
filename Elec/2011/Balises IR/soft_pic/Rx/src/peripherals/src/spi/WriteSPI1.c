/********************************************************************
*     Function Name : WriteSPI1                                     *
*     Description   : This routine writes a single byte/word to     * 
*                     the SPI bus.                                  *
*     Parameters    : Single data byte/word for SPI bus             *
*     Return Value  : None                                          *
********************************************************************/

#include "spi.h"

#if defined(_SPI_V2)
void WriteSPI1(unsigned int data_out)
{   
    if (SPI1CON1bits.MODE16)          /* word write */
        SPI1BUF = data_out;
    else 
        SPI1BUF = data_out & 0xff;   /*  byte write  */
}
#elif defined(_SPI_V1)
void WriteSPI1(unsigned int data_out)
{   
    if (SPI1CONbits.MODE16)          /* word write */
        SPI1BUF = data_out;
    else 
        SPI1BUF = data_out & 0xff;   /*  byte write  */
}
#endif
