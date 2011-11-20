#include <incap.h>

#ifdef _IC9IF

/********************************************************************
*    Function Name:  ReadCapture9                                   *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture9(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC9CON1bits.ICBNE)
	{
		*buffer++ = IC9BUF; /* reads the input capture buffer */
	}
#else
	while (IC9CONbits.ICBNE)
	{
		*buffer++ = IC9BUF; /* reads the input capture buffer */
	}
#endif

}
#else
#warning "Does not build on this target"
#endif
