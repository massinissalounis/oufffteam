/******************************************************************************
*    Function Name:  MasterReadI2C2
*    Description:    This routine reads a single byte from the I2C Bus. 
*                    To enable master receive,RCEN bit is set.
*                    The RCEN bit is checked until it is cleared.When cleared,
*                    the receive register is full and it's contents are 
*                    returned.
*    Parameters:     void
*    Return Value:   unsigned char
*******************************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

unsigned char MasterReadI2C2(void)
{
    I2C2CONbits.RCEN = 1;
    while(I2C2CONbits.RCEN);
    I2C2STATbits.I2COV = 0;
    return(I2C2RCV);
}

#else
#warning "Does not build on this target"
#endif

