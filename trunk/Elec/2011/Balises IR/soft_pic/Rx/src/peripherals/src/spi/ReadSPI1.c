/******************************************************************************
*     Function Name :   ReadSPI1                                              *
*     Description   :   This function will read single byte/ word  from SPI   *
*                       bus. If SPI is configured for byte  communication     *
*                       then upper byte of SPIBUF is masked.                  *         
*     Parameters    :   None                                                  *
*     Return Value  :   contents of SPIBUF register                           *
******************************************************************************/

#include "spi.h"

#if defined(_SPI_V2)
unsigned int ReadSPI1()
{         
    /* Check for Receive buffer full status bit of status register*/
    if (SPI1STATbits.SPIRBF)
    { 
        SPI1STATbits.SPIROV = 0;
                
        if (SPI1CON1bits.MODE16)
            return (SPI1BUF);           /* return word read */
        else
            return (SPI1BUF & 0xff);    /* return byte read */
    }
    return -1;                		/* RBF bit is not set return error*/
}
#elif defined(_SPI_V1)
unsigned int ReadSPI1()
{         
    /* Check for Receive buffer full status bit of status register*/
    if (SPI1STATbits.SPIRBF)
    { 
        SPI1STATbits.SPIROV = 0;
                
        if (SPI1CONbits.MODE16)
            return (SPI1BUF);           /* return word read */
        else
            return (SPI1BUF & 0xff);    /* return byte read */
    }
    return -1;                 		/* RBF bit is not set return error*/
}
#endif
