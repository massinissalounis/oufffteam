#include "dac.h"

#ifdef _DAC1LIF

/*********************************************************************
* Function Name     : CloseDAC1
* Description       : This function turns off the D/A converter. 
*                     Also, the Interrupt enable (DAIE) and Interrupt 
*                     flag (DAIF) bits are cleared
* Parameters        : None
* Return Value      : None
*********************************************************************/

void CloseDAC1(void)
{

    /* Turn off DAC */
    DAC1CONbits.DACEN = 0;  

	/* Clearing ACLKCON, DAC1STAT, DAC1CON registers */
	ACLKCON	= ACLKCON_VALUE;
	DAC1STAT = DAC1STAT_VALUE;
	DAC1CON = DAC1CON_VALUE;

    /* Clearing the Interrupt Flag bit */
	IFS4bits.DAC1RIF = 0;
  
    /* Disable the Interrupt */
    IEC4bits.DAC1RIE = 0;

	/* Clearing the Interrupt Flag bit */
	IFS4bits.DAC1LIF = 0;
  
    /* Disable the Interrupt */
    IEC4bits.DAC1LIE = 0;
}

#else
#warning "Does not build on this target"
#endif
