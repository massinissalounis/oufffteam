#include <incap.h>

#ifdef _IC10IF

/********************************************************************
*    Function Name:  ReadCapture10                                  *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture10(unsigned int * buffer)
{

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	while (IC10CON1bits.ICBNE)
	{
		*buffer++ = IC10BUF; /* reads the input capture buffer */
	}
#else
	while (IC10CONbits.ICBNE)
	{
		*buffer++ = IC10BUF; /* reads the input capture buffer */
	}
#endif

}

#else
#warning "Does not build on this target"
#endif
