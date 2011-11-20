#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP9IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair9
* Description       : This function starts the conversion of channels AN19 and AN18   
*                     if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair9(void)

 {
   	/* Start conversion of Analog ch AN19 and AN18 */
	ADCPC4bits.SWTRG9 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

