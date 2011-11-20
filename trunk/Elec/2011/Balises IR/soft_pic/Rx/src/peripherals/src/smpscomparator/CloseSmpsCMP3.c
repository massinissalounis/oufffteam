#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpscmp.h"
#ifdef _AC3IF

/*************************************************************************
* Function Name     : CloseSmpsCMP3
* Description       : This function disables the Comparator 3 module and clears the CMP 
*                     Interrupt Flags. This function also clears the CMPCON3 register.                   
* Parameters        : void
* Return Value      : None 
**************************************************************************/

void CloseSmpsCMP3(void)
                    
{
    
    /* Clear the CMP Interrupt status Flags of Comparator 3 */

	ClearSmpsCMP3IntFlag();

   /* Clear the CMP Interrupt control registers of Comparator 3 */

	DisableIntSmpsCMP3();
	
    /* Clear the CMP control registers */
	CMPCON3     = 0;
            
}
#else
#warning "Does not build on this target"
#endif
 
