#include <incap.h>

#ifdef _IC4IF

/********************************************************************
*    Function Name:  ReadCapture4                                   *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture4(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC4CON1bits.ICBNE)
	{
		*buffer++ = IC4BUF; /* reads the input capture buffer */
	}
#else
	while (IC4CONbits.ICBNE)
	{
		*buffer++ = IC4BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif
