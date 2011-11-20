#include <incap.h>

#ifdef _IC5IF

/********************************************************************
*    Function Name:  ReadCapture5                                   *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture5(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC5CON1bits.ICBNE)
	{
		*buffer++ = IC5BUF; /* reads the input capture buffer */
	}
#else
	while (IC5CONbits.ICBNE)
	{
		*buffer++ = IC5BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif
