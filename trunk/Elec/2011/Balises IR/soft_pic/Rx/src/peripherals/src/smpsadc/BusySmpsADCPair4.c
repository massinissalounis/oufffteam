#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP4IF 

/*************************************************************************
* Function Name     : BusySmpsADCPair4
* Description       : This function returns the conversion status of ADC channels AN9 and AN8.                     
* Parameters        : None 
* Return Value      : If the value of PEND is ‘1’, then ‘0’ is returned, indicating that the ADC is busy in conversion.
*                     If the value of PEND is ‘0’, then ‘1’ is returned, indicating that the ADC has completed conversion. 
**************************************************************************/

char BusySmpsADCPair4(void)
{

     return (!ADCPC2bits.PEND4); /* returns the conversion status of  ADC channels AN9 and AN8 */
}



#else
#warning "Does not build on this target"
#endif
 

