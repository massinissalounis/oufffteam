#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP6IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair6
* Description       : This function starts the conversion of channels AN13 and AN12   
*                     if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair6(void)

 {
   	/* Start conversion of Analog ch AN11 and AN10 */
	ADCPC3bits.SWTRG6 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

