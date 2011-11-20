#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP4IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair4
* Description       : This function starts the conversion of channels AN9 and AN8   
*                     if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair4(void)

 {
   	/* Start conversion of Analog ch AN9 and AN8 */
	ADCPC2bits.SWTRG4 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

