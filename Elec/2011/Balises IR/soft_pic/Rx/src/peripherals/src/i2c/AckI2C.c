/*********************************************************************
*    Function Name:  AckI2C
*    Description:    This routine generates acknowledge condition 
*                    during master receive.
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

void AckI2C(void)
{
	I2CCONbits.ACKDT = 0;
	I2CCONbits.ACKEN = 1;
}

#else
#warning "Does not build on this target"
#endif
