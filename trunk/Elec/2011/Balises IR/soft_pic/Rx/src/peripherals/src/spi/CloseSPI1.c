#include "spi.h"

/********************************************************************
*     Function Name :  CloseSPI1                                    *
*     Description   :  This routine disables the SPI module and its *
*                      interrupt bits.                              *
*     Parameters    :  None                                         *
*     Return Value  :  None                                         *
********************************************************************/

void CloseSPI1()
{ 
  
      _SPI1IE = 0;      /* Disable the Interrupt bit in the 
                                Interrupt Enable Control Register */
      SPI1STATbits.SPIEN = 0;   /* Disable the module. All pins controlled
                                by PORT Functions */
      _SPI1IF = 0;      /* Disable the Interrupt flag bit in the
                                Interrupt Flag Control Register */    
}
