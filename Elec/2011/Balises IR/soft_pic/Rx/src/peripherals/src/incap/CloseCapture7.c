#include <incap.h>

#ifdef _IC7IF

/********************************************************************
*    Function Name:  CloseCapture7                                  *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture7()
{
    _IC7IE = 0; /* disable the interrupt flag */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	IC7CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC7CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif

    _IC7IF = 0; /* disable the interrupt flag */
}

#else
#warning "Does not build on this target"
#endif

