#include <incap.h>

#ifdef _IC9IF

/********************************************************************
*    Function Name:  CloseCapture9                                  *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture9()
{
    _IC9IE = 0; /* disable the interrupt flag */

#if defined(__dsPIC33E__) || defined(__PIC24E__)  	
 	IC9CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
    IC9CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif
   
    _IC9IF = 0; /* disable the interrupt flag */
  
}
#else
#warning "Does not build on this target"
#endif
