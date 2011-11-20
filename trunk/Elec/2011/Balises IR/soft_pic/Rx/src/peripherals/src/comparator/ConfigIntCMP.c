#if defined(__dsPIC33F__) 
#include <p33Fxxxx.h>
#elif defined(__dsPIC24H__)
#include <p24Hxxxx.h>
#elif defined(__dsPIC33E__)
#include <p33Exxxx.h>
#endif

#include "comparator.h"
#if defined (_COMPARATOR_V1) || defined (_COMPARATOR_V2)


/*************************************************************************
* Function Name     : ConfigIntCMP
* Description       : This function clears the Interrupt Flag bits, sets the interrupt 
*                     priorities and Enables/disables the interrupts for comparator                          
* Parameters        : unsigned int cmp_intp, unsigned int cmp_intp_priority
* Return Value      : None 
**************************************************************************/

void ConfigIntCMP(unsigned int cmp_intp, unsigned int cmp_intp_priority)
{

    /* Clear the CMP Interrupt status Flags of comparator  */
	IFS1bits.CMIF = 0;

	/* Enable/Disable the CMP Interrupt of comparator  */
	IEC1bits.CMIE = cmp_intp;

	/* Set the priority of CMP interrupt for comparator  */
	IPC4bits.CMIP = cmp_intp_priority;
	
}

#else
#warning "Does not build on this target"
#endif
 
