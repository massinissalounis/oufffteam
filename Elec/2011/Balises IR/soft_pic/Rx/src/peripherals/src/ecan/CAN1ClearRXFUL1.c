#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1ClearRXFUL1
* Description       : This function clears the RXFUL1 register
*                     
* Parameters        : None
*                     
* Return Value      : None 
*********************************************************************/

void CAN1ClearRXFUL1(void)
{  
   C1RXFUL1 = 0x0000; 
   
}

#else
#warning "Does not build on this target"
#endif
