#include "dac.h"

#ifdef _DAC1LIF

/*********************************************************************
* Function Name     	: ConfigIntDAC1R
* Description       	: This function configures right channel DAC Interrupt.
* Parameters        	: unsigned int config
* Return Value     	: None
*********************************************************************/

void ConfigIntDAC1R(unsigned int config)
{
	/* Clearing the Interrupt Flag bit */
	IFS4bits.DAC1RIF = 0;
	
	/* Setting Priority */
	IPC19bits.DAC1RIP = config & 0x07;
	
	/* Setting the Interrupt enable bit */
	IEC4bits.DAC1RIE = (config & 0x08)>>3;

}

#else
#warning "Does not build on this target"
#endif
