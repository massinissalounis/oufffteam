#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP11IF 

/*************************************************************************
* Function Name     : BusySmpsADCPair11
* Description       : This function returns the conversion status of ADC channels AN23 and AN22.                     
* Parameters        : None 
* Return Value      : If the value of PEND is ‘1’, then ‘0’ is returned, indicating that the ADC is busy in conversion.
*                     If the value of PEND is ‘0’, then ‘1’ is returned, indicating that the ADC has completed conversion. 
**************************************************************************/

char BusySmpsADCPair11(void)
{

     return (!ADCPC5bits.PEND11); /* returns the conversion status of  ADC channels AN23 and AN22 */
}



#else
#warning "Does not build on this target"
#endif
 

