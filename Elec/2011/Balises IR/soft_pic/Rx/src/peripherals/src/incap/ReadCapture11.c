#include <incap.h>

#ifdef _IC11IF

/********************************************************************
*    Function Name:  ReadCapture11                                  *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture11(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC11CON1bits.ICBNE)
	{
		*buffer++ = IC11BUF; /* reads the input capture buffer */
	}
#else
	while (IC11CONbits.ICBNE)
	{
		*buffer++ = IC11BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif
