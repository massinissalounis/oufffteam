/************************************************************************
*    Function Name:  DataRdyI2C1	
*    Description:    This routine provides the status whether the receive 
*                    buffer is full by returning the RBF bit.
*    Parameters:     void
*    Return Value:   RBF bit status
*************************************************************************/

#include "i2c.h"

#if defined(_MI2C1IF)

char DataRdyI2C1(void)
{
     return I2C1STATbits.RBF;
}

#else
#warning "Does not build on this target"
#endif
