/******************************************************************************
*     Function Name :   ReadSPI2                                              *
*     Description   :   This function will read single byte/ word  from SPI   *
*                       bus. If SPI is configured for byte  communication     *
*                       then upper byte of SPIBUF is masked.                  *         
*     Parameters    :   None                                                  *
*     Return Value  :   contents of SPIBUF register                           *
******************************************************************************/

#include "spi.h"

#if defined(_SPI2IF)

#if defined(_SPI_V2)
unsigned int ReadSPI2()
{         
    /* Check for Receive buffer full status bit of status register*/
    if (SPI2STATbits.SPIRBF)
    {
        SPI2STATbits.SPIROV = 0;
                
        if (SPI2CON1bits.MODE16)
            return ( SPI2BUF );        /* return word read */
        else
            return (SPI2BUF & 0xff);   /* return byte read */
    }
	return -1;                         /* RBF bit is not set return error*/
}
#elif defined(_SPI_V1)
unsigned int ReadSPI2()
{         
    /* Check for Receive buffer full status bit of status register*/
    if (SPI2STATbits.SPIRBF)
    {
        SPI2STATbits.SPIROV = 0;
                
        if (SPI2CONbits.MODE16)
            return ( SPI2BUF );        /* return word read */
        else
            return (SPI2BUF & 0xff);   /* return byte read */
    }
	return -1;                         /* RBF bit is not set return error*/
}
#endif

#else
#warning "Does not build on this target"
#endif
