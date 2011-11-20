/************************************************************************
*    Function Name:  MasterWriteI2C2
*    Description:    This routine is used to write a byte to the I2C bus.
*                    The input parameter data_out is written to the 
*                    I2CTRN register. If IWCOL bit is set,write collision 
*                    has occured and -1 is returned, else 0 is returned.
*    Parameters:     unsigned char : data_out
*    Return Value:   unsigned int
*************************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

char MasterWriteI2C2(unsigned char data_out)
{
    I2C2TRN = data_out;

    if(I2C2STATbits.IWCOL)        /* If write collision occurs,return -1 */
        return -1;
    else
    {
        while(I2C2STATbits.TRSTAT);  // wait until write cycle is complete 
        IdleI2C2();                  // ensure module is idle
        if ( I2C2STATbits.ACKSTAT ) // test for ACK condition received
    	 return ( -2 );
	    else return ( 0 );               // if WCOL bit is not set return non-negative #
    }
}

#else
#warning "Does not build on this target"
#endif
