/*********************************************************************
*    Function Name:  StopI2C2
*    Description:    This routine generates Stop condition 
*                    during master mode.
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

void StopI2C2(void)
{
     I2C2CONbits.PEN = 1;	/* initiate Stop on SDA and SCL pins */
}

#else
#warning "Does not build on this target"
#endif
