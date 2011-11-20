#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP7IF


/*************************************************************************
* Function Name     : ConvertSmpsADCPair7
* Description       : This function starts the conversion of channels AN15 and AN14  
*                     if Software trigger source is selected.                 
* Parameters        : None
* Return Value      : None 
**************************************************************************/

void ConvertSmpsADCPair7(void)

 {
   	/* Start conversion of Analog ch AN15 and AN14*/
	ADCPC3bits.SWTRG7 = 1;
     
 }
#else
#warning "Does not build on this target"
#endif
 

