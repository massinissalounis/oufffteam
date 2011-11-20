#include <adc.h>

#ifdef _AD2IF

/*********************************************************************
* Function Name     : CloseADC2
* Description       : This function turns off the A/D converter. 
*                     Also, the Interrupt enable (ADIE) and Interrupt 
*                     flag (ADIF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseADC2(void)
{
    /* disable ADC interrupt */
    IEC1bits.AD2IE = 0;

    /* turn off ADC */
    AD2CON1bits.ADON = 0;

    /* clear ADIF bit */
    IFS1bits.AD2IF = 0;
}

#else
#warning "Does not build on this target"
#endif
