/****************************************************************************
*    Function Name:  SlaveWriteI2C
*    Description:    This routine is used to write a byte to the I2C bus.
*                    The input parameter data_out is written to the 
*                    I2CTRN register.
*    Parameters:     unsigned char : data_out
*    Return Value:   None
******************************************************************************/

#include "i2c.h"

#if defined(_MI2C1IF)

void SlaveWriteI2C1(unsigned char data_out)
{
     I2C1TRN = data_out;      /* data transferred to I2C1TRN reg */
     I2C1CONbits.SCLREL = 1;	/* Release the clock */
}

#else
#warning "Does not build on this target"
#endif
