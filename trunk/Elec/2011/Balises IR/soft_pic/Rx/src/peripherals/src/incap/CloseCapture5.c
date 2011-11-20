#include <incap.h>

#ifdef _IC5IF

/********************************************************************
*    Function Name:  CloseCapture5                                  *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture5()
{
    _IC5IE = 0; /* disable the interrupt */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	IC5CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC5CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif

    _IC5IF = 0; /* disable the interrupt flag */
}

#else
#warning "Does not build on this target"
#endif
