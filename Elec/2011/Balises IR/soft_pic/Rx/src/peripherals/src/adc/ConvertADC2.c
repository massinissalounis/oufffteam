#include <adc.h>

#ifdef _AD2IF

/*********************************************************************
* Function Name     : ConvertADC2
* Description       : This function starts an A/D conversion by 
*                     clearing ADCON1<SAMP> bit.
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConvertADC2(void)
{
     AD2CON1bits.SAMP = 0; /* clear SAMP bit to start conversion */
}

#else
#warning "Does not build on this target"
#endif
