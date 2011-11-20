#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP2IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair2
* Description       : This function starts the conversion of channels AN5 and AN4   
*                     if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair2(void)

 {
   	/* Start conversion of Analog ch AN5 and AN4 */
	ADCPC1bits.SWTRG2 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

