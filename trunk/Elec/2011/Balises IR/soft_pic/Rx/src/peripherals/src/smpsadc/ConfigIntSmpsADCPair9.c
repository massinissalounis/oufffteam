#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP9IF 


/*************************************************************************
* Function Name     : ConfigIntSmpsADCPair9
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for ADC channels AN19 and AN18                        
* Parameters        : unsigned int adc_intp - 0: disabled, 1: enabled
*		    , unsigned int adc_intp_priority - 0 to 7
* Return Value      : None 
**************************************************************************/

void ConfigIntSmpsADCPair9(unsigned int adc_intp, unsigned int adc_intp_priority)
{

        /* Clear the ADC Interrupt status Flags of ADC channels AN19 and AN18 */
	ClearSmpsADCIntPair9();

	/* Enable/Disable the ADC Interrupt of ADC channels AN19 and AN18 */
	SetIntSmpsADCPair9(adc_intp);

	/* Set the priority of ADC interrupt for ADC channels AN19 and AN18 */
	SetPriorityIntSmpsADCPair9(adc_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
