/**************************************************************************
*    Function Name:  SlaveputsI2C
*    Description:    This routine is used to write out a string to the 
*                    I2C bus.If write collision occurs,-3 is sent.If 
*                    string is written and null char reached, 0 is returned.
*    Parameters:     unsigned char * : wrptr
*    Return Value:   unsigned int
****************************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

unsigned int SlaveputsI2C(unsigned char * wrptr)
{
    I2CCONbits.STREN = 1;            /* SCL clock stretch enable bit */
    while(*wrptr)	             /* transmit data until null char */
    {
        SlaveputcI2C(*wrptr++);	     /* Send a byte */
	while(I2CSTATbits.TBF);	     /* wait til the transmit buffer is clear */ 
        while(!IFS0bits.SI2CIF);     /* Wait til the ACK from master is received */
        IFS0bits.SI2CIF = 0;
    }
    return 0;                        /* null char was reached */
}

#else
#warning "Does not build on this target"
#endif
