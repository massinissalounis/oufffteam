/*********************************************************************
*    Function Name:  RestartI2C
*    Description:    This routine generates Restart condition 
*                    during master mode.
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

void RestartI2C(void)
{ 
    I2CCONbits.RSEN = 1;	/* initiate restart on SDA and SCL pins	*/
}

#else
#warning "Does not build on this target"
#endif
