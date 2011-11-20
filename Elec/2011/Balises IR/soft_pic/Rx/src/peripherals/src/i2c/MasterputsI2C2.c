/***********************************************************************
*    Function Name:  MasterputsI2C2
*    Description:    This routine is used to write out a string to the 
*                    I2C bus.If write collision occurs,-3 is sent.If 
*                    Nack is received, -2 is sent.If string is written 
*                    and null char reached, 0 is returned.
*    Parameters:     unsigned char * : wrptr
*    Return Value:   unsigned int 
************************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

unsigned int MasterputsI2C2(unsigned char * wrptr)
{
    while(*wrptr)                           //transmit data until null char
    {
        if(MasterputcI2C2(*wrptr) == -1)	    // write a byte
        return -3;                          //return with write collison error

        while(I2C2STATbits.TBF);             //Wait till data is transmitted.

        IdleI2C2();
        wrptr++;
    }
    return 0;			
}

#else
#warning "Does not build on this target"
#endif
