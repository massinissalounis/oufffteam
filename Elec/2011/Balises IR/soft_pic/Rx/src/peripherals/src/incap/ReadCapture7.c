#include <incap.h>

#ifdef _IC7IF

/********************************************************************
*    Function Name:  ReadCapture7                                   *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture7(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC7CON1bits.ICBNE)
	{
		*buffer++ = IC7BUF; /* reads the input capture buffer */
	}
#else
	while (IC7CONbits.ICBNE)
	{
		*buffer++ = IC7BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif
