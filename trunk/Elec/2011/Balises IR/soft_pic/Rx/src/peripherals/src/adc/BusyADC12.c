#include "adc12.h"

#ifdef _ADC_12BIT

/*********************************************************************
* Function Name     : BusyADC12
* Description       : This function returns the ADC conversion status.
* Parameters        : None
* Return Value      : DONE bit status
*********************************************************************/

char BusyADC12(void)
{
    return !(ADCON1bits.DONE); /* returns the DONE bit status */
}

#else
#warning "Does not build on this target"
#endif

