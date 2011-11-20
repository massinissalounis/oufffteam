/**********************************************************************
*    Function Name:  SlaveReadI2C2
*    Description:    This routine reads a single byte from the I2C Bus. 
*                    The RBF bit is checked until it is set.When set,
*                    the receive register is full and it's contents are
*                    returned.					 
*    Parameters:     void
*    Return Value:   unsigned char
***********************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

unsigned char SlaveReadI2C2(void)
{
     while(!I2C2STATbits.RBF);
     I2C2STATbits.I2COV = 0;
     return(I2C2RCV);
}

#else
#warning "Does not build on this target"
#endif


