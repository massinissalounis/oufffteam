#include <adc.h>

#ifdef _AD1IF

/*********************************************************************
* Function Name     : BusyADC1
* Description       : This function returns the ADC conversion status.
* Parameters        : None
* Return Value      : DONE bit status
*********************************************************************/

char BusyADC1(void)
{
    return !(AD1CON1bits.DONE);	/* returns the DONE bit status */
}

#else
#warning "Does not build on this target"
#endif
