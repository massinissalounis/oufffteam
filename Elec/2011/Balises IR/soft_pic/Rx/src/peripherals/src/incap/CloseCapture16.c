#include <incap.h>

#ifdef _IC16IF

/********************************************************************
*    Function Name:  CloseCapture16                                 *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture16()
{
    _IC16IE = 0; /* disable the interrupt flag */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  	
 	IC16CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC16CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif
   
    _IC16IF = 0; /* disable the interrupt flag */
  
}
#else
#warning "Does not build on this target"
#endif
