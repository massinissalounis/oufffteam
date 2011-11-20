#include <incap.h>

#ifdef _IC14IF

/********************************************************************
*    Function Name:  CloseCapture14                                 *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture14()
{
    _IC14IE = 0; /* disable the interrupt flag */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  	
 	IC14CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC14CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif
   
    _IC14IF = 0; /* disable the interrupt flag */
  
}
#else
#warning "Does not build on this target"
#endif
