/*********************************************************************
*    Function Name:  RestartI2C1
*    Description:    This routine generates Restart condition 
*                    during master mode.
*    Parameters:     void    
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#if defined(_MI2C1IF)

void RestartI2C1(void)
{ 
    I2C1CONbits.RSEN = 1;	/* initiate restart on SDA and SCL pins	*/
}

#else
#warning "Does not build on this target"
#endif
