#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP1IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair1
* Description       : This function starts the conversion of channels AN3 and AN2   
*                     if if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair1(void)

 {
   	/* Start conversion of Analog ch AN3 and AN2 */
	ADCPC0bits.SWTRG1 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

