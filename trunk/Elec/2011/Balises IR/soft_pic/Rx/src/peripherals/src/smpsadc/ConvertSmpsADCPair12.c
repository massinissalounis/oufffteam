#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP12IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair12
* Description       : This function starts the conversion of channels AN25 and AN24   
*                     if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair12(void)

 {
   	/* Start conversion of Analog ch AN25 and AN24 */
	ADCPC6bits.SWTRG12 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

