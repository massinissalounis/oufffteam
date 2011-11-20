/*********************************************************************
*    Function Name:  StopI2C
*    Description:    This routine generates Stop condition 
*                    during master mode.
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

void StopI2C(void)
{
     I2CCONbits.PEN = 1;	/* initiate Stop on SDA and SCL pins */
}

#else
#warning "Does not build on this target"
#endif
