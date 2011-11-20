#include "dac.h"

#ifdef _DAC1LIF

/*********************************************************************
* Function Name     	: OpenDAC1
* Description       	: Configures the DAC. 
* Parameters        	: config1, config2, config3
* Return Value      	: None
*********************************************************************/

void OpenDAC1(unsigned int config1, unsigned int config2, unsigned int config3)
{
	/* Clear configuration registers */
	ACLKCON	= ACLKCON_VALUE;
	DAC1STAT = DAC1STAT_VALUE;
	DAC1CON = DAC1CON_VALUE;
	
	/* Configure ACLKCON */
	ACLKCON = config3;
	
	/* Configure DAC1STAT */
    	DAC1STAT = config2;

    	/* Configure DAC1CON */
    	DAC1CON = config1;
}

#else
#warning "Does not build on this target"
#endif
