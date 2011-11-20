#include <incap.h>

#ifdef _IC2IF

/********************************************************************
*    Function Name:  ReadCapture2                                   *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture2(unsigned int * buffer)
{
#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC2CON1bits.ICBNE)
	{
		*buffer++ = IC2BUF; /* reads the input capture buffer */
	}
#else
	while (IC2CONbits.ICBNE)
	{
		*buffer++ = IC2BUF; /* reads the input capture buffer */
	}
#endif
}

#else
#warning "Does not build on this target"
#endif
