#include "spi.h"

/************************************************************************
*     Function Name :  ConfigIntSPI1                                    *
*     Description   :  This Function Configures Interrupt and sets      *
*                      Interrupt Priority                               *
*     Parameters    :  unsigned int config                              *
*     Return Value  :  None                                             *
************************************************************************/

void ConfigIntSPI1( unsigned int config)
{
    _SPI1IF = 0;                   /* Clear IF bit */
    _SPI1IP = (config &0x0007);    /* Assign interrupt priority */
    _SPI1IE = (config &0x0008)>>3; /* Interrupt Enable/Disable bit */
}
