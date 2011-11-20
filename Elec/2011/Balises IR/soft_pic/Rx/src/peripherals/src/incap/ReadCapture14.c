#include <incap.h>

#ifdef _IC14IF

/********************************************************************
*    Function Name:  ReadCapture14                                  *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture14(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC14CON1bits.ICBNE)
	{
		*buffer++ = IC14BUF; /* reads the input capture buffer */
	}
#else
	while (IC14CONbits.ICBNE)
	{
		*buffer++ = IC14BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif

