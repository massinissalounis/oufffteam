/************************************************************************
*    Function Name:  MastergetsI2C
*    Description:    This routine reads predetermined data string length
*                    from the I2C bus.
*    Parameters:     unsigned int    : length
*                    unsigned char * : rdptr
*    Return Value:   unsigned int
*************************************************************************/

#include "i2c.h"

#if defined(_MI2C1IF)

unsigned int MastergetsI2C1(unsigned int length, unsigned char * rdptr, 
                            unsigned int i2c1_data_wait)
{
    int wait = 0;
    while(length)                    /* Receive length bytes */
    {
        I2C1CONbits.RCEN = 1;
        while(!DataRdyI2C1())
        {
            if(wait < i2c1_data_wait)
                wait++ ;                 
            else
            return(length);          /* Time out, 
                                        return number of byte/word to be read */
        }
        wait = 0;
        *rdptr = I2C1RCV;            /* save byte received */
        rdptr++;
        length--;
        if(length == 0)              /* If last char, generate NACK sequence */
        {
            I2C1CONbits.ACKDT = 1;
            I2C1CONbits.ACKEN = 1;
        }
        else                         /* For other chars,generate ACK sequence */
        {
            I2C1CONbits.ACKDT = 0;
            I2C1CONbits.ACKEN = 1;
        }
            while(I2C1CONbits.ACKEN == 1);    /* Wait till ACK/NACK sequence 
                                                 is over */
    }
    /* return status that number of bytes specified by length was received */
    return 0;
}

#else
#warning "Does not build on this target"
#endif
