#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP9IF 

/*************************************************************************
* Function Name     : BusySmpsADCPair9
* Description       : This function returns the conversion status of ADC channels AN19 and AN18.                     
* Parameters        : None 
* Return Value      : If the value of PEND is ‘1’, then ‘0’ is returned, indicating that the ADC is busy in conversion.
*                     If the value of PEND is ‘0’, then ‘1’ is returned, indicating that the ADC has completed conversion. 
**************************************************************************/

char BusySmpsADCPair9(void)
{

     return (!ADCPC4bits.PEND9); /* returns the conversion status of  ADC channels AN19 and AN18 */
}



#else
#warning "Does not build on this target"
#endif
 

