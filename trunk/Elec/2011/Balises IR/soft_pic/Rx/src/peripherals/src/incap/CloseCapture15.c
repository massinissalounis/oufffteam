#include <incap.h>

#ifdef _IC15IF

/********************************************************************
*    Function Name:  CloseCapture10                                 *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture15()
{
    _IC15IE = 0; /* disable the interrupt flag */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  	
 	IC15CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC15CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif
   
    _IC15IF = 0; /* disable the interrupt flag */
  
}
#else
#warning "Does not build on this target"
#endif
