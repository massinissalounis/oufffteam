/*********************************************************************
*    Function Name:  AckI2C1
*    Description:    This routine generates acknowledge condition 
*                    during master receive.
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#if defined(_MI2C1IF)

void AckI2C1(void)
{
	I2C1CONbits.ACKDT = 0;
	I2C1CONbits.ACKEN = 1;
}

#else
#warning "Does not build on this target"
#endif
