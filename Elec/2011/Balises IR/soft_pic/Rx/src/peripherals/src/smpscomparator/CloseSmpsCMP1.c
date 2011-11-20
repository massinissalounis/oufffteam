#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpscmp.h"
#ifdef _AC1IF

/*************************************************************************
* Function Name     : CloseSmpsCMP1
* Description       : This function disables the Comparator 1 module and clears the CMP 
*                     Interrupt Flags. This function also clears the CMPCON1 register.                   
* Parameters        : void
* Return Value      : None 
**************************************************************************/

void CloseSmpsCMP1(void)
                    
{
    
    /* Clear the CMP Interrupt status Flags of Comparator 1 */

	ClearSmpsCMP1IntFlag();

   /* Clear the CMP Interrupt control registers of Comparator 1 */

	DisableIntSmpsCMP1();
	
    /* Clear the CMP control registers */
	CMPCON1     = 0;
            
}
#else
#warning "Does not build on this target"
#endif
 
