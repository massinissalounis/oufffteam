#include <incap.h>

#ifdef _IC1IF

/********************************************************************
*    Function Name:  CloseCapture1                                  *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture1()
{
	
    _IC1IE = 0; /* disable the interrupt flag */
   
#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	 IC1CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
     IC1CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif

    _IC1IF = 0; /* disable the interrupt flag */
}

#else
#warning "Does not build on this target"
#endif
