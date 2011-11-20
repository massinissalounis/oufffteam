/************************************************************************
*    Function Name:  SlavegetsI2C1	
*    Description:    This routine reads bytes from the I2C bus until  
*                    stop bit is received.
*    Parameters:     unsigned char * : rdptr
*                    unsigned int    : i2c_data_wait			
*    Return Value:   unsigned int    : number of bytes received
*************************************************************************/

#include "i2c.h"

#if defined(_MI2C1IF)

unsigned int SlavegetsI2C1(unsigned char * rdptr, unsigned int i2c1_data_wait)
{
    int i = 0;                          /* indicates number of bytes received */
    int wait = 0;
    unsigned char temp = I2C1RCV;        /* flush out old data already on 
                                            I2CRCV to clear RBF flag */

    I2C1STATbits.I2COV = 0;              /* clear OV flag */

    while(!I2C1STATbits.P)               /* check for stop bit */
    {
        while(!DataRdyI2C1())
        {
            if(wait < i2c1_data_wait)    /* timeout check */
                wait++ ;                 
            else
                return i;                /* return number of bytes received */		
        }
        wait = 0;
        *rdptr++ = I2C1RCV;             /* save byte received */

        i++;                            /* Increment the number of bytes read */

        if((I2C1CONbits.STREN) && (!I2C1CONbits.SCLREL))
            I2C1CONbits.SCLREL = 1;	/* Clock is released after ACK */

    }
    return i;				/* return number of bytes received */
}

#else
#warning "Does not build on this target"
#endif
