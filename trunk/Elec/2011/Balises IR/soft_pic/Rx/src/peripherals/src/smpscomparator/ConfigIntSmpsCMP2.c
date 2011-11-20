#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpscmp.h"
#ifdef _AC2IF 


/*************************************************************************
* Function Name     : ConfigIntSmpsCMP2
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for comparator 2                         
* Parameters        : unsigned int cmp_intp (Either CMPx_INT_EN or CMPx_INT_DIS)
*                     unsigned int cmp_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntSmpsCMP2(unsigned int cmp_intp, unsigned int cmp_intp_priority)
{

    /* Clear the CMP Interrupt status Flags of comparator 1 */
	ClearSmpsCMP2IntFlag();

	/* Enable/Disable the CMP Interrupt of comparator 1 */
	if (cmp_intp == CMP2_INT_EN)
	{
		EnableIntSmpsCMP2();
	}
	else
	{
		DisableIntSmpsCMP2();
	}

	/* Set the priority of CMP interrupt for comparator 1 */
	SetPriorityIntSmpsCMP2(cmp_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
