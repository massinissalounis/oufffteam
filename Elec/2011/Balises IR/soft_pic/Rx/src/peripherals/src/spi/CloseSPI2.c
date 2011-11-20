/********************************************************************
*     Function Name :  CloseSPI2                                    *
*     Description   :  This routine disables the SPI module and its *
*                      interrupt bits.                              * 
*     Parameters    :  None                                         *
*     Return Value  :  None                                         *
********************************************************************/

#include "spi.h"

#if defined(_SPI2IF)

void CloseSPI2( )
{
      _SPI2IE = 0;      /* Disable the Interrupt bit in the 
                                   Interrupt Enable Control Register */
      SPI2STATbits.SPIEN = 0;       /* Disable the module. All pins controlled
                                   by PORT Functions */
      _SPI2IF = 0;      /* Disable the Interrupt flag bit in the 
                                   Interrupt Flag Control Register */    
}

#else
#warning "Does not build on this target"
#endif
