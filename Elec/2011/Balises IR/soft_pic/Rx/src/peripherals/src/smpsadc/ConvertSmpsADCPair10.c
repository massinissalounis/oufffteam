#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP10IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair10
* Description       : This function starts the conversion of channels AN21 and AN20   
*                     if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair10(void)

 {
   	/* Start conversion of Analog ch AN21 and AN20 */
	ADCPC5bits.SWTRG10 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

