#include <incap.h>

#ifdef _IC15IF

/********************************************************************
*    Function Name:  ReadCapture15                                  *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture15(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC15CON1bits.ICBNE)
	{
		*buffer++ = IC15BUF; /* reads the input capture buffer */
	}
#else
	while (IC15CONbits.ICBNE)
	{
		*buffer++ = IC15BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif