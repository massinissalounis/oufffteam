/*********************************************************************
*    Function Name:  StartI2C
*    Description:    This routine generates Start condition 
*                    during master mode.
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

void StartI2C(void)
{
     I2CCONbits.SEN = 1;	/* initiate Start on SDA and SCL pins */
}

#else
#warning "Does not build on this target"
#endif
