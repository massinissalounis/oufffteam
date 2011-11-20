#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP12IF 

/*************************************************************************
* Function Name     : BusySmpsADCPair12
* Description       : This function returns the conversion status of ADC channels AN25 and AN24.                     
* Parameters        : None 
* Return Value      : If the value of PEND is ‘1’, then ‘0’ is returned, indicating that the ADC is busy in conversion.
*                     If the value of PEND is ‘0’, then ‘1’ is returned, indicating that the ADC has completed conversion. 
**************************************************************************/

char BusySmpsADCPair12(void)
{

     return (!ADCPC6bits.PEND12); /* returns the conversion status of  ADC channels AN25 and AN24 */
}



#else
#warning "Does not build on this target"
#endif
 

