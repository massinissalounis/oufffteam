#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP8IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair8
* Description       : This function starts the conversion of channels AN17 and AN16  
*                     if if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair8(void)

 {
   	/* Start conversion of Analog ch AN17 and AN16 */
	ADCPC4bits.SWTRG8 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

