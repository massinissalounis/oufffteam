#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpscmp.h"
#ifdef _AC4IF


/*************************************************************************
* Function Name     : OpenSmpsCMP4
* Description       : This function configures the Comparator 4 Module                      
* Parameters        : unsigned int config
* Return Value      : None 
**************************************************************************/

void OpenSmpsCMP4(unsigned int config)
{
    CMPCON4   = config ; 
	
}
#else
#warning "Does not build on this target"
#endif
 

