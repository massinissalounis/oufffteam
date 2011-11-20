#if defined(__dsPIC30F__) 
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "smpscmp.h"
#ifdef _AC4IF 


/*************************************************************************
* Function Name     : ConfigIntSmpsCMP4
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for comparator 4                         
* Parameters        : unsigned int cmp_intp (Either CMPx_INT_EN or CMPx_INT_DIS)
*                     unsigned int cmp_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntSmpsCMP4(unsigned int cmp_intp, unsigned int cmp_intp_priority)
{

    /* Clear the CMP Interrupt status Flags of comparator 1 */
	ClearSmpsCMP4IntFlag();

	/* Enable/Disable the CMP Interrupt of comparator 1 */
	if (cmp_intp == CMP4_INT_EN)
	{
		EnableIntSmpsCMP4();
	}
	else
	{
		DisableIntSmpsCMP4();
	}

	/* Set the priority of CMP interrupt for comparator 1 */
	SetPriorityIntSmpsCMP4(cmp_intp_priority);
	
}

#else
#warning "Does not build on this target"
#endif
 
