#include <incap.h>

#ifdef _IC6IF

/********************************************************************
*    Function Name:  CloseCapture6                                  *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture6()
{
    _IC6IE = 0;         /* disable the interrupt */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	IC6CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC6CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif

    _IC6IF = 0;         /* disable the interrupt flag */
}

#else
#warning "Does not build on this target"
#endif
