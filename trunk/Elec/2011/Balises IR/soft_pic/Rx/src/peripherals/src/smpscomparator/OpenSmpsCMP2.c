#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpscmp.h"
#ifdef _AC2IF


/*************************************************************************
* Function Name     : OpenSmpsCMP2
* Description       : This function configures the Comparator 2 Module                      
* Parameters        : unsigned int config
* Return Value      : None 
**************************************************************************/

void OpenSmpsCMP2(unsigned int config)
{
    CMPCON2   = config ; 
	
}
#else
#warning "Does not build on this target"
#endif
 
