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

#if defined(_MI2C1IF)

unsigned char SlaveReadI2C1(void)
{
     while(!I2C1STATbits.RBF);
     I2C1STATbits.I2COV = 0;
     return(I2C1RCV);

}

#else
#warning "Does not build on this target"
#endif
