#include <incap.h>

#ifdef _IC4IF

/********************************************************************
*    Function Name:  CloseCapture4                                  *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture4()
{
    _IC4IE = 0; /* disable the interrupt */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	IC4CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC4CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif

    _IC4IF = 0; /* disable the interrupt flag */
}

#else
#warning "Does not build on this target"
#endif
