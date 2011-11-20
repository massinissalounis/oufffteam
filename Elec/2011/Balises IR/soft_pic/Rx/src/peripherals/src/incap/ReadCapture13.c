#include <incap.h>

#ifdef _IC13IF

/********************************************************************
*    Function Name:  ReadCapture13                                  *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture13(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC13CON1bits.ICBNE)
	{
		*buffer++ = IC13BUF; /* reads the input capture buffer */
	}
#else
	while (IC13CONbits.ICBNE)
	{
		*buffer++ = IC13BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif
