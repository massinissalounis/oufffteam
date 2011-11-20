#include <incap.h>

#ifdef _IC8IF

/********************************************************************
*    Function Name:  CloseCapture8                                  *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture8()
{
    _IC8IE = 0; /* disable the interrupt */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	IC8CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC8CONbits.ICM = 0;  /* Input Capture x(ic_no) Off */
#endif

    _IC8IF = 0; /* disable the interrupt flag */
}

#else
#warning "Does not build on this target"
#endif
