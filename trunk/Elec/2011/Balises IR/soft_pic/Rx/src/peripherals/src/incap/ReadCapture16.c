#include <incap.h>

#ifdef _IC16IF

/********************************************************************
*    Function Name:  ReadCapture16                                  *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture16(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC16CON1bits.ICBNE)
	{
		*buffer++ = IC16BUF; /* reads the input capture buffer */
	}
#else
	while (IC16CONbits.ICBNE)
	{
		*buffer++ = IC16BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif

