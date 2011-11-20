#include "adc10.h"

#ifdef _ADC_10BIT

/*********************************************************************
* Function Name     : BusyADC10
* Description       : This function returns the ADC conversion status.
* Parameters        : None
* Return Value      : DONE bit status
*********************************************************************/

char BusyADC10(void)
{
    return !(ADCON1bits.DONE);	/* returns the DONE bit status */
}

#else
#warning "Does not build on this target"
#endif

