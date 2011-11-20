#include <incap.h>

#ifdef _IC12IF

/********************************************************************
*    Function Name:  ReadCapture12                                  *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture12(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC12CON1bits.ICBNE)
	{
		*buffer++ = IC12BUF; /* reads the input capture buffer */
	}
#else
	while (IC12CONbits.ICBNE)
	{
		*buffer++ = IC12BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif
