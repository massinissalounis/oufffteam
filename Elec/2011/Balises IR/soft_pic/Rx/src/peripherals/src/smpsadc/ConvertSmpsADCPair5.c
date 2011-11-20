#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP5IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair5
* Description       : This function starts the conversion of channels AN11 and AN10   
*                     if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair5(void)

 {
   	/* Start conversion of Analog ch AN11 and AN10 */
	ADCPC2bits.SWTRG5 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

