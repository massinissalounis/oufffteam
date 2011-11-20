#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpsadc.h"
#ifdef _ADCP0IF


/*************************************************************************
* Function Name     : ConfigSmpsADCPort
* Description       : This function configures the ADC Port Pin to Analog or Digital Port                      
* Parameters        : unsigned int config1 - 0:Analog , 1:Digital
* Return Value      : None 
**************************************************************************/

void ConfigSmpsADCPort(unsigned int config1)
{
    ADPCFG   = config1 ; 
	
}
#else
#warning "Does not build on this target"
#endif
 

