#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP1IF 


/*************************************************************************
* Function Name     : ConfigIntSmpsADCPair1
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for ADC channels AN3 and AN2                        
* Parameters        : unsigned int adc_intp - 0: disabled, 1: enabled
*		    , unsigned int adc_intp_priority - 0 to 7
* Return Value      : None 
**************************************************************************/

void ConfigIntSmpsADCPair1(unsigned int adc_intp, unsigned int adc_intp_priority)
{

        /* Clear the ADC Interrupt status Flags of ADC channels AN3 and AN2 */
	ClearSmpsADCIntPair1();

	/* Enable/Disable the ADC Interrupt of ADC channels AN3 and AN2 */
	SetIntSmpsADCPair1(adc_intp);

	/* Set the priority of ADC interrupt for ADC channels AN3 and AN2 */
	SetPriorityIntSmpsADCPair1(adc_intp_priority);
}

#else
#warning "Does not build on this target"
#endif
 
