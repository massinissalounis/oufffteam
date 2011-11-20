/****************************************************************************
*     Function Name :  getsSPI1                                             *
*     Description   :  This routine reads a string from the SPI             *
*                      receive buffer.The number of byte/word to be read    *
*                      is determined by parameter 'length'                  *
*     Parameters    :  unsigned int length: The length of data expected     *
*                      unsigned int *rdptr   the received data to be        *
*                      recorded to this array                               *  
*                      unsigned int uart_data_wait timeout value            *
*     Return Value  :  unsigned int number of data bytes yet to be received *                     
****************************************************************************/

#include "spi.h"

#if defined(_SPI_V2)
unsigned int getsSPI1(unsigned int length, unsigned int *rdptr, unsigned int spi_data_wait)
{
    int wait = 0;
    char *temp_ptr = (char *)rdptr;
    while (length)                     /* stay in loop until length = 0  */
    {
        while(!DataRdySPI1())
        {

           if(wait < spi_data_wait)
               wait++ ;                /* wait for time out operation */
           else
               return(length);         /*Time out, return number of byte/word to be read */
        }
        wait = 0;
        
        if(SPI1CON1bits.MODE16)
            *rdptr++ = getcSPI1();     /* read a single word */
        else
            *temp_ptr++ = getcSPI1();  /* read a single byte */
        length--;                      /* reduce string length count by 1*/
    }
    return (length);                   /* return number of byte/word to be read i.e, 0 */
}
#elif defined(_SPI_V1)
unsigned int getsSPI1(unsigned int length, unsigned int *rdptr, unsigned int spi_data_wait)
{
    int wait = 0;
    char *temp_ptr = (char *)rdptr;
    while (length)                     /* stay in loop until length = 0  */
    {
        while(!DataRdySPI1())
        {

           if(wait < spi_data_wait)
               wait++ ;                /* wait for time out operation */
           else
               return(length);         /*Time out, return number of byte/word to be read */
        }
        wait = 0;
        
        if(SPI1CONbits.MODE16)
            *rdptr++ = getcSPI1();     /* read a single word */
        else
            *temp_ptr++ = getcSPI1();  /* read a single byte */
        length--;                      /* reduce string length count by 1*/
    }
    return (length);                   /* return number of byte/word to be read i.e, 0 */
}
#endif
