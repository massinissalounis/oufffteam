#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpscmp.h"
#ifdef _AC3IF


/*************************************************************************
* Function Name     : OpenSmpsCMP3
* Description       : This function configures the Comparator 3 Module                      
* Parameters        : unsigned int config
* Return Value      : None 
**************************************************************************/

void OpenSmpsCMP3(unsigned int config)
{
    CMPCON3   = config ; 
	
}
#else
#warning "Does not build on this target"
#endif
 

