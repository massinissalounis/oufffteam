#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1ClearRXFUL2
* Description       : This function clears the RXFUL2 register
*                     
* Parameters        : None
*                     
* Return Value      : None 
*********************************************************************/

void CAN1ClearRXFUL2(void)
{  
   C1RXFUL2 = 0x0000; 
   
}

#else
#warning "Does not build on this target"
#endif
