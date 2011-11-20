/************************************************************************
*    Function Name:  SlavegetsI2C	
*    Description:    This routine reads bytes from the I2C bus until  
*                    stop bit is received.
*    Parameters:     unsigned char * : rdptr
*                    unsigned int    : i2c_data_wait			
*    Return Value:   unsigned int    : number of bytes received
*************************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

unsigned int SlavegetsI2C(unsigned char * rdptr, unsigned int i2c_data_wait)
{
    int i = 0;                          /* indicates number of bytes received */
    int wait = 0;
    unsigned char temp = I2CRCV;        /* flush out old data already on 
                                           I2CRCV to clear RBF flag */

    I2CSTATbits.I2COV = 0;              /* clear OV flag */

    while(!I2CSTATbits.P)               /* check for stop bit */
    {
        while(!DataRdyI2C())
        {
            if(wait < i2c_data_wait)    /* timeout check */
                wait++ ;                 
            else
                return i;               /* return number of bytes received */		
        }
        wait = 0;
        *rdptr++ = I2CRCV;              /* save byte received */

        i++;                            /* Increment the number of bytes read */

        if((I2CCONbits.STREN) && (!I2CCONbits.SCLREL))
            I2CCONbits.SCLREL = 1;	/* Clock is released after ACK */

    }
    return i;				/* return number of bytes received */
}

#else
#warning "Does not build on this target"
#endif
