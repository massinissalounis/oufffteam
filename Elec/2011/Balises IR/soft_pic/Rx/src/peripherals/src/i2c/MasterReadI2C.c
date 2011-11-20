/******************************************************************************
*    Function Name:  MasterReadI2C
*    Description:    This routine reads a single byte from the I2C Bus. 
*                    To enable master receive,RCEN bit is set.
*                    The RCEN bit is checked until it is cleared.When cleared,
*                    the receive register is full and it's contents are 
*                    returned.
*    Parameters:     void
*    Return Value:   unsigned char
*******************************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

unsigned char MasterReadI2C(void)
{
    I2CCONbits.RCEN = 1;
    while(I2CCONbits.RCEN);
    I2CSTATbits.I2COV = 0;
    return(I2CRCV);
}

#else
#warning "Does not build on this target"
#endif

