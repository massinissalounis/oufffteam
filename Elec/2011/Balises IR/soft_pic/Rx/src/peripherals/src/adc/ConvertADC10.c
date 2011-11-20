#include "adc10.h"

#ifdef _ADC_10BIT

/*********************************************************************
* Function Name     : ConvertADC10
* Description       : This function starts an A/D conversion by 
*                     clearing ADCON1<SAMP> bit.
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConvertADC10(void)
{
     ADCON1bits.SAMP = 0; /* clear SAMP to start conversion*/
}

#else
#warning "Does not build on this target"
#endif
