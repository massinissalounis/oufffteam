#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1ClearRXOVF1
* Description       : This function clears the RXOVF1 register
*                     
* Parameters        : None
*                     
* Return Value      : None 
*********************************************************************/

void CAN1ClearRXOVF1(void)
{  
   C1RXOVF1 = 0x0000; 
   
}

#else
#warning "Does not build on this target"
#endif
