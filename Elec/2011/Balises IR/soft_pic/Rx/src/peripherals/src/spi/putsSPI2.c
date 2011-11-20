/******************************************************************************
*     Function Name :  putsSPI2                                               *
*     Description   :  This function writes the specified length of data      *
*                      word/byte to be transmitted into the transmit buffer   *
*     Parameters    :  unsigned int: length of bytes/words to be written      *
*                      unsigned int*:  Address ofthe location where the data  *
*                      to be transmitted is stored                            *
*     Return Value  :  None                                                   *                                                                
******************************************************************************/

#include "spi.h"

#if defined(_SPI2IF)

#if defined(_SPI_V2)
void putsSPI2(unsigned int length, unsigned int *wrptr)
{  
    char *temp_ptr = (char *) wrptr;
    while (length)                   /* write byte/word until length is 0 */
    {           
        if(SPI2CON1bits.MODE16)
            SPI2BUF = *wrptr++;      /* initiate SPI bus cycle by word write */ 
        else
            SPI2BUF = *temp_ptr++;   /* initiate SPI bus cycle by byte write */ 
        while(SPI2STATbits.SPITBF);  /* wait until 'SPITBF' bit is cleared */
        length--;                    /* decrement length */
    }
}
#elif defined(_SPI_V1)
void putsSPI2(unsigned int length, unsigned int *wrptr)
{  
    char *temp_ptr = (char *) wrptr;
    while (length)                   /* write byte/word until length is 0 */
    {           
        if(SPI2CONbits.MODE16)
            SPI2BUF = *wrptr++;      /* initiate SPI bus cycle by word write */ 
        else
            SPI2BUF = *temp_ptr++;   /* initiate SPI bus cycle by byte write */ 
        while(SPI2STATbits.SPITBF);  /* wait until 'SPITBF' bit is cleared */
        length--;                    /* decrement length */
    }
}
#endif

#else
#warning "Does not build on this target"
#endif
