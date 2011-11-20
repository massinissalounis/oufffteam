#include <adc.h>

#ifdef _AD2IF

/*********************************************************************
* Function Name     : BusyADC2
* Description       : This function returns the ADC conversion status.
* Parameters        : None
* Return Value      : DONE bit status
*********************************************************************/

char BusyADC2(void)
{

    return !(AD2CON1bits.DONE); /* returns the DONE bit status */
}

#else
#warning "Does not build on this target"
#endif


