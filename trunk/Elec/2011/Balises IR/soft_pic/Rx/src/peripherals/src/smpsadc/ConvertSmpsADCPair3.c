#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP3IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair3
* Description       : This function starts the conversion of channels AN7 and AN6   
*                     if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair3(void)

 {
   	/* Start conversion of Analog ch AN7 and AN6 */
	ADCPC1bits.SWTRG3 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

