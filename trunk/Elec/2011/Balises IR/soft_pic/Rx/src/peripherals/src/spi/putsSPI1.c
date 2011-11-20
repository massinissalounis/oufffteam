/*****************************************************************************
*     Function Name :  putsSPI1                                              *
*     Description   :  This function writes the specified length of data     *
*                      word/byte to be transmitted into the transmit buffer  *
*     Parameters    :  unsigned int: length of bytes/words to be written     *
*                      unsigned int*:  Address ofthe location where the data *
*                      to be transmitted is stored                           *
*     Return Value  :  None                                                  *                                                                
*****************************************************************************/

#include "spi.h"

#if defined(_SPI_V2)
void putsSPI1(unsigned int length, unsigned int *wrptr)
{  
    char *temp_ptr = (char *) wrptr;
    while (length)                   /* write byte/word until length is 0 */
    {            
        if(SPI1CON1bits.MODE16)
            SPI1BUF = *wrptr++;      /* initiate SPI bus cycle by word write */ 
        else
            SPI1BUF = *temp_ptr++;   /* initiate SPI bus cycle by byte write */ 
        while(SPI1STATbits.SPITBF);  /* wait until 'SPITBF' bit is cleared */
        length--;                    /* decrement length */
    }
}
#elif defined(_SPI_V1)
void putsSPI1(unsigned int length, unsigned int *wrptr)
{  
    char *temp_ptr = (char *) wrptr;
    while (length)                   /* write byte/word until length is 0 */
    {            
        if(SPI1CONbits.MODE16)
            SPI1BUF = *wrptr++;      /* initiate SPI bus cycle by word write */ 
        else
            SPI1BUF = *temp_ptr++;   /* initiate SPI bus cycle by byte write */ 
        while(SPI1STATbits.SPITBF);  /* wait until 'SPITBF' bit is cleared */
        length--;                    /* decrement length */
    }
}
#endif
