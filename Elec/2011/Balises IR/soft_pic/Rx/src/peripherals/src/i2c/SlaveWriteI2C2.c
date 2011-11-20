/****************************************************************************
*    Function Name:  SlaveWriteI2C
*    Description:    This routine is used to write a byte to the I2C bus.
*                    The input parameter data_out is written to the 
*                    I2CTRN register.
*    Parameters:     unsigned char : data_out
*    Return Value:   None
******************************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

void SlaveWriteI2C2(unsigned char data_out)
{
     I2C2TRN = data_out;      /* data transferred to I2C2TRN reg */
     I2C2CONbits.SCLREL = 1;	/* Release the clock */
}

#else
#warning "Does not build on this target"
#endif
