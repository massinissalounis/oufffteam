#include "dac.h"

#ifdef _DAC1LIF

/*********************************************************************
* Function Name     	: ConfigIntDAC1L
* Description       	: This function configures left channel DAC Interrupt.
* Parameters        	: unsigned int config
* Return Value     	: None
*********************************************************************/

void ConfigIntDAC1L(unsigned int config)
{
    	/* Clearing the Interrupt Flag bit */
	IFS4bits.DAC1LIF = 0;

    	/* Setting Priority */
    	IPC19bits.DAC1LIP = config & 0x07;
  
    	/* Setting the Interrupt enable bit */
    	IEC4bits.DAC1LIE = (config & 0x08)>>3;

}

#else
#warning "Does not build on this target"
#endif
