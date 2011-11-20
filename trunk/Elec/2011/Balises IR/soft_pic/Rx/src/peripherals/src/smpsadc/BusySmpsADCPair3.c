#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP3IF 

/*************************************************************************
* Function Name     : BusySmpsADCPair3
* Description       : This function returns the conversion status of ADC channels AN7 and AN6.                     
* Parameters        : None 
* Return Value      : If the value of PEND is ‘1’, then ‘0’ is returned, indicating that the ADC is busy in conversion.
*                     If the value of PEND is ‘0’, then ‘1’ is returned, indicating that the ADC has completed conversion. 
**************************************************************************/

char BusySmpsADCPair3(void)
{

     return (!ADCPC1bits.PEND3); /* returns the conversion status of  ADC channels AN7 and AN6 */
}



#else
#warning "Does not build on this target"
#endif
 

