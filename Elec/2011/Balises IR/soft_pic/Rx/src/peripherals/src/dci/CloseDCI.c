#include "dci.h"

#ifdef _DCIIF

/**************************************************************************
*    Function Name  : CloseDCI
*    Description    : This routine Disables the DCI module and its
*	              interrupt bits
*    Return Value   : None
*    Parameters:    : None
***************************************************************************/

void CloseDCI(void)
{
     _DCIEN = 0; /* Disable the DCI module */
     _DCIIE = 0;    /* Disable the Interrupt bit in IEC Register */
     _DCIIF = 0;    /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
