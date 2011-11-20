#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP1IF


/*************************************************************************
* Function Name     : ConfigSmpsADCTrigSource1
* Description       : This function enables/ disables common interrupt generation and  
*                     configures the ADC trigger source for channels AN3 and AN2                     
* Parameters        : unsigned int adc_common_intp- 0: disabled, 1: enabled
*                   ; unsigned int config1- Trigger Source 
* Return Value      : None 
**************************************************************************/

void ConfigSmpsADCTrigSource1(unsigned int adc_common_intp, unsigned int config1)

 {
   	/* Enable/Disable the ADC common Interrupt request for Analog ch AN3 and AN2 */
	SetCommonIntSmpsADCPair1(adc_common_intp);

	/* Enables to select the Trigger source for conversion of Analog ch AN3 and AN2 */
        ADCPC0bits.TRGSRC1  = ((config1 & 0x1F00) >> 8); 

 }
#else
#warning "Does not build on this target"
#endif
 

