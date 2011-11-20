/************************************************************************
*    Function Name:  DataRdyI2C	
*    Description:    This routine provides the status whether the receive 
*                    buffer is full by returning the RBF bit.
*    Parameters:     void
*    Return Value:   RBF bit status
*************************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

char DataRdyI2C(void)
{
     return I2CSTATbits.RBF;
}

#else
#warning "Does not build on this target"
#endif
