#include <incap.h>

#ifdef _IC6IF

/********************************************************************
*    Function Name:  ReadCapture6                                   *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture6(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC6CON1bits.ICBNE)
	{
		*buffer++ = IC6BUF; /* reads the input capture buffer */
	}
#else
	while (IC6CONbits.ICBNE)
	{
		*buffer++ = IC6BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif
