#include <incap.h>

#ifdef _IC2IF

/********************************************************************
*    Function Name:  CloseCapture2                                  *
*    Description:    This routine disable the inputcapture and its  *
*                    interrupt bits.                                *
*    Parameters:     None                                           *
*    Return Value:   None                                           *
********************************************************************/

void CloseCapture2()
{
    _IC2IE = 0; /* disable the interrupt */
    
#if defined(__dsPIC33E__) || defined(__PIC24E__)  
	 IC2CON1bits.ICM = 0; /* Input Capture x(ic_no) Off */
#else
	 IC2CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
#endif

    _IC2IF = 0; /* disable the interrupt flag */
}

#else
#warning "Does not build on this target"
#endif

