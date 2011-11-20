/******************************************************************************
*    Function Name:  MasterReadI2C1
*    Description:    This routine reads a single byte from the I2C Bus. 
*                    To enable master receive,RCEN bit is set.
*                    The RCEN bit is checked until it is cleared.When cleared,
*                    the receive register is full and it's contents are 
*                    returned.
*    Parameters:     void
*    Return Value:   unsigned char
********************************************************************************/

#include "i2c.h"

#if defined(_MI2C1IF)

unsigned char MasterReadI2C1(void)
{
    I2C1CONbits.RCEN = 1;
    while(I2C1CONbits.RCEN);
    I2C1STATbits.I2COV = 0;
    return(I2C1RCV);
}

#else
#warning "Does not build on this target"
#endif


