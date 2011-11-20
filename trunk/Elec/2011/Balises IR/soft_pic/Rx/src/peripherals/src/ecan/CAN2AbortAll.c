#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name:     CAN2AbortAll
* Description:       This function sets the ABAT bit in C2CTRL1 register 
*                    thus initiating the abort of all pending transmissions
* Parameters:        None
* Return Value:      None 
*********************************************************************/

void CAN2AbortAll(void)
{
   C2CTRL1bits.ABAT = 1;
}

#else
#warning "Does not build on this target"
#endif
