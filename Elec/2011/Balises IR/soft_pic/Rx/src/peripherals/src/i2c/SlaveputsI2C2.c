/**************************************************************************
*    Function Name:  SlaveputsI2C2
*    Description:    This routine is used to write out a string to the 
*                    I2C bus.If write collision occurs,-3 is sent.If 
*                    string is written and null char reached, 0 is returned.
*    Parameters:     unsigned char * : wrptr
*    Return Value:   unsigned int
****************************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

unsigned int SlaveputsI2C2(unsigned char * wrptr)
{
    I2C2CONbits.STREN = 1;           /* SCL clock stretch enable bit */
    while(*wrptr)	             /* transmit data until null char */
    {
        SlaveputcI2C2(*wrptr++);     /* Send a byte */
	while(I2C2STATbits.TBF);     /* wait til the transmit buffer is clear */
        while(!IFS3bits.SI2C2IF);    /* Wait til the ACK from master is received */
        IFS3bits.SI2C2IF = 0;
    }
    return 0;                        /* null char was reached */
}

#else
#warning "Does not build on this target"
#endif
