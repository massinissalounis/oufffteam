#include <incap.h>

#ifdef _IC3IF

/********************************************************************
*    Function Name:  CloseCapture3                                  *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture3()
{
    _IC3IE = 0; /* disable the interrupt */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	IC3CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC3CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif

    _IC3IF = 0; /* disable the interrupt flag */
}

#else
#warning "Does not build on this target"
#endif
