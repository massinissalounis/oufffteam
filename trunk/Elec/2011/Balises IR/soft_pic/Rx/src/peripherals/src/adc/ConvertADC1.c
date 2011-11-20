#include <adc.h>

#ifdef _AD1IF

/*********************************************************************
* Function Name     : ConvertADC1
* Description       : This function starts an A/D conversion by 
*                     clearing ADCON1<SAMP> bit.
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConvertADC1(void)
{
     AD1CON1bits.SAMP = 0; /* clear SAMP to start conversion*/
}

#else
#warning "Does not build on this target"
#endif
