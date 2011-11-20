#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP0IF

/*************************************************************************
* Function Name     : ConfigIntSmpsADCGlobal
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for ADC pair                       
* Parameters        : unsigned int adc_intp - 0: disabled, 1: enabled
*		    , unsigned int adc_intp_priority - 0 to 7
* Return Value      : None 
**************************************************************************/

void ConfigIntSmpsADCGlobal(unsigned int adc_intp, unsigned int adc_intp_priority)
{

        /* Clear the ADC Interrupt status Flags   */
	ClearSmpsADCIntGlobal();

	/* Enable/Disable the ADC Interrupt of ADC  */
	SetIntSmpsADCGlobal(adc_intp); 

	/* Set the priority of ADC interrupt for ADC   */
	SetPriorityIntSmpsADCGlobal(adc_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
