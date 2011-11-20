/*********************************************************************
*    Function Name:  StartI2C2
*    Description:    This routine generates Start condition 
*                    during master mode.
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

void StartI2C2(void)
{
     I2C2CONbits.SEN = 1;	/* initiate Start on SDA and SCL pins */
}

#else
#warning "Does not build on this target"
#endif
