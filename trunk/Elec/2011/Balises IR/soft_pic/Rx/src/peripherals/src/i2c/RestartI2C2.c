/*********************************************************************
*    Function Name:  RestartI2C2
*    Description:    This routine generates Restart condition 
*                    during master mode.
*    Parameters:     void    
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

void RestartI2C2(void)
{ 
    I2C2CONbits.RSEN = 1;	/* initiate restart on SDA and SCL pins	*/
}

#else
#warning "Does not build on this target"
#endif
