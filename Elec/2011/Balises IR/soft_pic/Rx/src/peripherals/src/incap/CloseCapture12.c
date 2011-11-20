#include <incap.h>

#ifdef _IC12IF

/********************************************************************
*    Function Name:  CloseCapture12                                 *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture12()
{
    _IC12IE = 0; /* disable the interrupt flag */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  	
 	IC12CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC12CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif
   
    _IC12IF = 0; /* disable the interrupt flag */
  
}
#else
#warning "Does not build on this target"
#endif
