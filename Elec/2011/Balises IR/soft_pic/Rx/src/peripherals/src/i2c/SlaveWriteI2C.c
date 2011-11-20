/****************************************************************************
*    Function Name:  SlaveWriteI2C
*    Description:    This routine is used to write a byte to the I2C bus.
*                    The input parameter data_out is written to the 
*                    I2CTRN register.
*    Parameters:     unsigned char : data_out
*    Return Value:   None
******************************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

void SlaveWriteI2C(unsigned char data_out)
{
     I2CTRN = data_out;      /* data transferred to I2CTRN reg */
     I2CCONbits.SCLREL = 1;	/* Release the clock */
}

#else
#warning "Does not build on this target"
#endif
