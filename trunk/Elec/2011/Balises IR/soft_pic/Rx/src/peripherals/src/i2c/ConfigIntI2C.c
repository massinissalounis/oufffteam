/*********************************************************************
*    Function Name:  ConfigIntI2C
*    Description:    This routine enables/disables the SI2C & MI2C  
*                    interrupts and sets their priorities
*    Parameters:     unsigned int : config	
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

void ConfigIntI2C(unsigned int config)
{                
     /* clear the MI2C & SI2C Interrupts */
     _SI2CIF = 0;
     _MI2CIF = 0;

     _SI2CIP = (config & 0x0007);       /* set the SI2C priority */
     _MI2CIP = (config & 0x0070) >> 4;  /* set the MI2C priority */

     _SI2CIE = (config & 0x0008)>> 3;   /* enable/disable SI2C Int */
     _MI2CIE = (config & 0x0080) >> 7;  /* enable/disable MI2C Int */
}

#else
#warning "Does not build on this target"
#endif
