#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP0IF


/*************************************************************************
* Function Name     : OpenSmpsADC
* Description       : This function configures the ADC Module                      
* Parameters        : unsigned int config1
* Return Value      : None 
**************************************************************************/

void OpenSmpsADC(unsigned int config1)
{
    ADCON   = config1 ; 
	
}
#else
#warning "Does not build on this target"
#endif
 

