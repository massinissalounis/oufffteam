#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP6IF


/*************************************************************************
* Function Name     : ConfigSmpsADCTrigSource6
* Description       : This function enables/ disables common interrupt generation and  
*                     configures the ADC trigger source for channels AN13 and AN12                     
* Parameters        : unsigned int adc_common_intp- 0: disabled, 1: enabled
*                   ; unsigned int config1- Trigger Source 
* Return Value      : None 
**************************************************************************/

void ConfigSmpsADCTrigSource6(unsigned int adc_common_intp, unsigned int config1)

 {
   	/* Enable/Disable the ADC common Interrupt request for Analog ch AN13 and AN12 */
	SetCommonIntSmpsADCPair6(adc_common_intp);

	/* Enables to select the Trigger source for conversion of Analog ch AN13 and AN12 */
        ADCPC3bits.TRGSRC6  = (config1 & 0x001F); 

 }
#else
#warning "Does not build on this target"
#endif
 
