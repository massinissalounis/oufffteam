/************************************************************************
*    Function Name:  IdleI2C	
*    Description:    This routine generates wait condition intil I2C 
*                    bus is Idle.					 
*    Parameters:     void
*    Return Value:   void
*************************************************************************/

#include "i2c.h"

#if defined(_MI2C1IF)

void IdleI2C1(void)
{
    /* Wait until I2C Bus is Inactive */
    while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || 
          I2C1CONbits.RSEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);	
}

#else
#warning "Does not build on this target"
#endif
