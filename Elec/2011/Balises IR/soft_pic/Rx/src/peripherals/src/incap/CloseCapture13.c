#include <incap.h>

#ifdef _IC13IF

/********************************************************************
*    Function Name:  CloseCapture13                                 *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture13()
{
    _IC13IE = 0; /* disable the interrupt flag */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  	
 	IC13CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC13CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif
   
    _IC13IF = 0; /* disable the interrupt flag */
  
}
#else
#warning "Does not build on this target"
#endif
