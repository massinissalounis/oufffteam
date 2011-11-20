#include <incap.h>

#ifdef _IC8IF

/********************************************************************
*    Function Name:  ReadCapture8                                   *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture8(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC8CON1bits.ICBNE)
	{
		*buffer++ = IC8BUF; /* reads the input capture buffer */
	}
#else
	while (IC8CONbits.ICBNE)
	{
		*buffer++ = IC8BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif
