/************************************************************************
*    Function Name:  IdleI2C	
*    Description:    This routine generates wait condition intil I2C 
*                    bus is Idle.					 
*    Parameters:     void
*    Return Value:   void
*************************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

void IdleI2C(void)
{
    /* Wait until I2C Bus is Inactive */
    while(I2CCONbits.SEN || I2CCONbits.PEN || I2CCONbits.RCEN || 
          I2CCONbits.ACKEN || I2CSTATbits.TRSTAT);	
}

#else
#warning "Does not build on this target"
#endif
