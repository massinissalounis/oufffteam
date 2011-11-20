/************************************************************************
*     Function Name :  ConfigIntSPI2                                    *
*     Description   :  This Function Configures Interrupt and sets      *
*                      Interrupt Priority                               *
*     Parameters    :  unsigned int config                              *
*     Return Value  :  None                                             *
************************************************************************/

#include "spi.h"

#if defined(_SPI2IF)

void ConfigIntSPI2( unsigned int config)
{
    _SPI2IF = 0;                   /* Clear IF bit */
    _SPI2IP = (config &0x0007);    /* Assign interrupt priority */
    _SPI2IE = (config &0x0008)>>3; /* Interrupt Enable/Disable bit */
}

#else
#warning "Does not build on this target"
#endif
