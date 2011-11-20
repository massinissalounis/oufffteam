#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP0IF

/*************************************************************************
* Function Name     : ReadSmpsADC
* Description       : This function reads from one of the 12 ADC Buffers
*                     (ADCBUF0 - ADCBUF11) for dsPIC30F devices and from
*		      one of the 26 ADC Buffers (ADCBUF0 - ADCBUF25) for
*		      dsPIC33F devices                        
* Parameters        : unsigned int buff_no 
* Return Value      : unsigned int 
**************************************************************************/

unsigned int ReadSmpsADC(unsigned int buff_no)
{

     return(*(&ADCBUF0+buff_no));
}



#else
#warning "Does not build on this target"
#endif
 
