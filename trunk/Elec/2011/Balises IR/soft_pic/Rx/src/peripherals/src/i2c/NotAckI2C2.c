/*********************************************************************
*    Function Name:  NotAckI2C1
*    Description:    This routine generates not acknowledge condition 
*                    during master receive.
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

void NotAckI2C2(void)
{
    I2C2CONbits.ACKDT = 1;
    I2C2CONbits.ACKEN = 1;
}

#else
#warning "Does not build on this target"
#endif
