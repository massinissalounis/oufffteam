/***********************************************************************
*    Function Name:  MasterputsI2C
*    Description:    This routine is used to write out a string to the 
*                    I2C bus.If write collision occurs,-3 is sent.If 
*                    Nack is received, -2 is sent.If string is written 
*                    and null char reached, 0 is returned.
*    Parameters:     unsigned char * : wrptr
*    Return Value:   unsigned int 
************************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

unsigned int MasterputsI2C(unsigned char * wrptr)
{
    while(*wrptr)                           //transmit data until null char
    {
        if(MasterputcI2C(*wrptr) == -1)	    // write a byte
        return -3;                          //return with write collison error

        while(I2CSTATbits.TBF);             //Wait till data is transmitted.

        IdleI2C();
        wrptr++;
    }
    return 0;			
}

#else
#warning "Does not build on this target"
#endif
