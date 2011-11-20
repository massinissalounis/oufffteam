#include <incap.h>

#ifdef _IC3IF

/********************************************************************
*    Function Name:  ReadCapture3                                   *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture3(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC3CON1bits.ICBNE)
	{
		*buffer++ = IC3BUF; /* reads the input capture buffer */
	}
#else
	while (IC3CONbits.ICBNE)
	{
		*buffer++ = IC3BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif
