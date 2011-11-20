#include <ecan.h>

#ifdef _C1TXIF

/**************************************************************************
* Function Name:     CAN1AbortAll
* Description:       This function sets the ABAT bit in C1CTRL1 register 
*                    thus initiating the abort of all pending transmissions
* Parameters:        None
* Return Value:      None 
***************************************************************************/

void CAN1AbortAll(void)
{
   C1CTRL1bits.ABAT = 1;
}

#else
#warning "Does not build on this target"
#endif
