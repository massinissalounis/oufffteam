#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1ClearRXOVF2
* Description       : This function clears the RXOVF2 register
*                     
* Parameters        : None
*                     
* Return Value      : None 
*********************************************************************/

void CAN1ClearRXOVF2(void)
{  
   C1RXOVF2 = 0x0000; 
   
}

#else
#warning "Does not build on this target"
#endif
