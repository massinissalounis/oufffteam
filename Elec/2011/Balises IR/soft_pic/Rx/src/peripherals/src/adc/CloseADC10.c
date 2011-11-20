#include "adc10.h"

#ifdef _ADC_10BIT

/*********************************************************************
* Function Name     : CloseADC10
* Description       : This function turns off the A/D converter. 
*                     Also, the Interrupt enable (ADIE) and Interrupt 
*                     flag (ADIF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseADC10(void)
{
    /* disable ADC interrupt */
    IEC0bits.ADIE = 0;

    /* turn off ADC */
    ADCON1bits.ADON = 0;    

	/* clear ADIF bit */
    IFS0bits.ADIF = 0;
}

#else
#warning "Does not build on this target"
#endif
