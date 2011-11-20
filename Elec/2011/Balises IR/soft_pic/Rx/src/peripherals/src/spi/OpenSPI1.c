/*******************************************************************************
*   Function Name :  OpenSPI1                                                  *
*   Description   :  This functionin Initializes the SPI module and also       *
*                    enables  SPI module                                       *
*   Parameters    :  unsigned int config1,unsigned int config2                 *
*   Return Value  :  None                                                      *
*   Note:            Config1 contains information about framed SPI support,    *
*                    frame sync pulse,Disable SDO pin, Word/byte communication *
*                     data input sample phase bit, clock edge select bit,slave *
*                    select ,clock polarity select bit ,Master enable bit      *
*                    secondary prescale bit, Primary prescale bit              *
*                    Config2 contains information about Enable/Disable SPI,SPI *
*                    Operation during CPU IDLE mode                            *
*******************************************************************************/

#include "spi.h"

#if defined(_SPI_V2)
void OpenSPI1(unsigned int config1, unsigned int config2, unsigned int config3)
{       
     SPI1CON1 = config1;      /* Initalizes the spi module */
     SPI1CON2 = config2;
     SPI1STAT = config3;     /* Enable/Disable the spi module */
}
#elif defined(_SPI_V1)
void OpenSPI1(unsigned int config1, unsigned int config2)
{       
     SPI1CON = config1;      /* Initalizes the spi module */
     SPI1STAT = config2;     /* Enable/Disable the spi module */
}
#endif
