#include "adc12.h"

#ifdef _ADC_12BIT

/*********************************************************************
* Function Name     : ConvertADC12
* Description       : This function starts an A/D conversion by 
*                     clearing ADCON1<SAMP> bit.
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConvertADC12(void)
{
     ADCON1bits.SAMP = 0; /* clear SAMP bit to start conversion */
}

#else
#warning "Does not build on this target"
#endif
