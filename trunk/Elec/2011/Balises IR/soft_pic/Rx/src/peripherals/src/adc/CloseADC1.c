#include <adc.h>

#ifdef _AD1IF

/*********************************************************************
* Function Name     : CloseADC1
* Description       : This function turns off the A/D converter. 
*                     Also, the Interrupt enable (ADIE) and Interrupt 
*                     flag (ADIF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseADC1(void)
{
    /* disable ADC interrupt */
    IEC0bits.AD1IE = 0;

    /* turn off ADC */
    AD1CON1bits.ADON = 0;    

	/* clear ADIF bit */
    IFS0bits.AD1IF = 0;
}

#else
#warning "Does not build on this target"
#endif
