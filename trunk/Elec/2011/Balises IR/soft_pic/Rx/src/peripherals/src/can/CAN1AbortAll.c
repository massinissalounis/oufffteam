#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/**************************************************************************
* Function Name:     CAN1AbortAll
* Description:       This function sets the ABAT bit in C1CTRL register 
*                    thus initiating the abort of all pending transmissions
* Parameters:        None
* Return Value:      None 
***************************************************************************/

void CAN1AbortAll(void)
{
   C1CTRLbits.ABAT = 1;
}

#else
#warning "Does not build on this target"
#endif

#endif

