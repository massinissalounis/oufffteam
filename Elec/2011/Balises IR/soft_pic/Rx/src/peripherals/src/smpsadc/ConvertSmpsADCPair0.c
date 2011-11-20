#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP0IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair0
* Description       : This function starts the conversion of channels AN1 and AN0   
*                     if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair0(void)

 {
   	/* Start conversion of Analog ch AN1 and AN0 */
	ADCPC0bits.SWTRG0 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

