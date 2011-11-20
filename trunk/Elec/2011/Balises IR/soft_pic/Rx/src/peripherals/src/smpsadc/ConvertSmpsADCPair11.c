#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP11IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair11
* Description       : This function starts the conversion of channels AN23 and AN22   
*                     if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair11(void)

 {
   	/* Start conversion of Analog ch AN23 and AN22 */
	ADCPC5bits.SWTRG11 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

