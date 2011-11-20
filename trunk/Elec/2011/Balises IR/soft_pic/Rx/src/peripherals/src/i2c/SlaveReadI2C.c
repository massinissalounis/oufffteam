/**********************************************************************
*    Function Name:  SlaveReadI2C
*    Description:    This routine reads a single byte from the I2C Bus. 
*                    The RBF bit is checked until it is set.When set,
*                    the receive register is full and it's contents are
*                    returned.					 
*    Parameters:     void
*    Return Value:   unsigned char
***********************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

unsigned char SlaveReadI2C(void)
{
     while(!I2CSTATbits.RBF);
     I2CSTATbits.I2COV = 0;
     return(I2CRCV);
}

#else
#warning "Does not build on this target"
#endif
