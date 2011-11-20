#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpscmp.h"
#ifdef _AC4IF

/*************************************************************************
* Function Name     : CloseSmpsCMP4
* Description       : This function disables the Comparator 4 module and clears the CMP 
*                     Interrupt Flags. This function also clears the CMPCON4 register.                   
* Parameters        : void
* Return Value      : None 
**************************************************************************/

void CloseSmpsCMP4(void)
                    
{
    
    /* Clear the CMP Interrupt status Flags of Comparator 4 */

	ClearSmpsCMP4IntFlag();

   /* Clear the CMP Interrupt control registers of Comparator 4 */

	DisableIntSmpsCMP4();
	
    /* Clear the CMP control registers */
	CMPCON4     = 0;
            
}
#else
#warning "Does not build on this target"
#endif
 
