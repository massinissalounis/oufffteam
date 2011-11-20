#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/*********************************************************************
* Function Name:     CAN2AbortAll
* Description:       This function sets the ABAT bit in C2CTRL register 
*                    thus initiating the abort of all pending transmissions
* Parameters:        None
* Return Value:      None 
*********************************************************************/

void CAN2AbortAll(void)
{
   C2CTRLbits.ABAT = 1;
}

#else
#warning "Does not build on this target"
#endif

#endif

