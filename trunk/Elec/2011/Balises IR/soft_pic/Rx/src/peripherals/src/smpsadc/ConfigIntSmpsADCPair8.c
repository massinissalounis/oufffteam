#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP8IF 


/*************************************************************************
* Function Name     : ConfigIntSmpsADCPair8
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for ADC channels AN17 and AN16                        
* Parameters        : unsigned int adc_intp - 0: disabled, 1: enabled
*		    , unsigned int adc_intp_priority - 0 to 7
* Return Value      : None 
**************************************************************************/

void ConfigIntSmpsADCPair1(unsigned int adc_intp, unsigned int adc_intp_priority)
{

        /* Clear the ADC Interrupt status Flags of ADC channels AN17 and AN16 */
	ClearSmpsADCIntPair8();

	/* Enable/Disable the ADC Interrupt of ADC channels AN17 and AN16 */
	SetIntSmpsADCPair8(adc_intp);

	/* Set the priority of ADC interrupt for ADC channels AN17 and AN16 */
	SetPriorityIntSmpsADCPair8(adc_intp_priority);
}

#else
#warning "Does not build on this target"
#endif
 
