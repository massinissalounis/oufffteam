#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpscmp.h"
#ifdef _AC2IF

/*************************************************************************
* Function Name     : CloseSmpsCMP2
* Description       : This function disables the Comparator 2 module and clears the CMP 
*                     Interrupt Flags. This function also clears the CMPCON2 register.                   
* Parameters        : void
* Return Value      : None 
**************************************************************************/

void CloseSmpsCMP2(void)
                    
{
    
    /* Clear the CMP Interrupt status Flags of Comparator 2 */

	ClearSmpsCMP2IntFlag();

   /* Clear the CMP Interrupt control registers of Comparator 2 */

	DisableIntSmpsCMP2();
	
    /* Clear the CMP control registers */
	CMPCON2     = 0;
            
}
#else
#warning "Does not build on this target"
#endif
 
