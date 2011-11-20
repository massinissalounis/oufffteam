/************************************************************************
*    Function Name:  SlavegetsI2C2	
*    Description:    This routine reads bytes from the I2C bus until  
*                    stop bit is received.
*    Parameters:     unsigned char * : rdptr
*                    unsigned int    : i2c_data_wait			
*    Return Value:   unsigned int    : number of bytes received
*************************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

unsigned int SlavegetsI2C2(unsigned char * rdptr, unsigned int i2c2_data_wait)
{
    int i = 0;                          /* indicates number of bytes received */
    int wait = 0;
    unsigned char temp = I2C2RCV;       /* flush out old data already on 
                                           I2CRCV to clear RBF flag */

    I2C2STATbits.I2COV = 0;             /* clear OV flag */

    while(!I2C2STATbits.P)              /* check for stop bit */
    {
        while(!DataRdyI2C2())
        {
            if(wait < i2c2_data_wait)   /* timeout check */
                wait++ ;                 
            else
                return i;               /* return number of bytes received */		
        }
        wait = 0;
        *rdptr++ = I2C2RCV;             /* save byte received */

        i++;                            /* Increment the number of bytes read */

        if((I2C2CONbits.STREN) && (!I2C2CONbits.SCLREL))
            I2C2CONbits.SCLREL = 1;	/* Clock is released after ACK */

    }
    return i;				/* return number of bytes received */
}

#else
#warning "Does not build on this target"
#endif
