/************************************************************************
*    Function Name:  IdleI2C2	
*    Description:    This routine generates wait condition intil I2C2 
*                    bus is Idle.					 
*    Parameters:     void
*    Return Value:   void
*************************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

void IdleI2C2(void)
{
    /* Wait until I2C Bus is Inactive */
    while(I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || 
          I2C2CONbits.RSEN ||I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT);	
}

#else
#warning "Does not build on this target"
#endif
