/************************************************************************
*    Function Name:  MastergetsI2C2
*    Description:    This routine reads predetermined data string length
*                    from the I2C bus.
*    Parameters:     unsigned int    : length
*                    unsigned char * : rdptr
*    Return Value:   unsigned int
*************************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

unsigned int MastergetsI2C2(unsigned int length, unsigned char * rdptr, 
                            unsigned int i2c2_data_wait)
{
    int wait = 0;
    while(length)                    /* Receive length bytes */
    {
        I2C2CONbits.RCEN = 1;
        while(!DataRdyI2C2())
        {
            if(wait < i2c2_data_wait)
                wait++ ;                 
            else
            return(length);          /* Time out, 
                                        return number of byte/word to be read */
        }
        wait = 0;
        *rdptr = I2C2RCV;            /* save byte received */
        rdptr++;
        length--;
        if(length == 0)              /* If last char, generate NACK sequence */
        {
            I2C2CONbits.ACKDT = 1;
            I2C2CONbits.ACKEN = 1;
        }
        else                         /* For other chars,generate ACK sequence */
        {
            I2C2CONbits.ACKDT = 0;
            I2C2CONbits.ACKEN = 1;
        }
            while(I2C2CONbits.ACKEN == 1);    /* Wait till ACK/NACK sequence 
                                                 is over */
    }
    /* return status that number of bytes specified by length was received */
    return 0;
}

#else
#warning "Does not build on this target"
#endif
