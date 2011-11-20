#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpscmp.h"
#ifdef _AC1IF


/*************************************************************************
* Function Name     : OpenSmpsCMP1
* Description       : This function configures the Comparator 1 Module                      
* Parameters        : unsigned int config
* Return Value      : None 
**************************************************************************/

void OpenSmpsCMP1(unsigned int config)
{
    CMPCON1   = config ; 
	
}
#else
#warning "Does not build on this target"
#endif
 

