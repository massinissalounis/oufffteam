#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP17IF


/*************************************************************************
* Function Name     : ConfigSmpsADCTrigSource7
* Description       : This function enables/ disables common interrupt generation and  
*                     configures the ADC trigger source for channels AN15 and AN14                     
* Parameters        : unsigned int adc_common_intp- 0: disabled, 1: enabled
*                   ; unsigned int config1- Trigger Source 
* Return Value      : None 
**************************************************************************/

void ConfigSmpsADCTrigSource7(unsigned int adc_common_intp, unsigned int config1)

 {
   	/* Enable/Disable the ADC common Interrupt request for Analog ch AN15 and AN14 */
	SetCommonIntSmpsADCPair7(adc_common_intp);

	/* Enables to select the Trigger source for conversion of Analog ch AN15 and AN14 */
        ADCPC3bits.TRGSRC7  = ((config1 & 0x1F00) >> 8); 

 }
#else
#warning "Does not build on this target"
#endif
 

