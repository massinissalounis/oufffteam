/*********************************************************************
*    Function Name:  StartI2C1
*    Description:    This routine generates Start condition 
*                    during master mode.
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#if defined(_MI2C1IF)

void StartI2C1(void)
{
     I2C1CONbits.SEN = 1;	/* initiate Start on SDA and SCL pins */
}

#else
#warning "Does not build on this target"
#endif
