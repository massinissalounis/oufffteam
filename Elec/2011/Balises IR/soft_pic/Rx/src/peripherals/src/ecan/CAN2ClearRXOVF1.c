#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2ClearRXOVF1
* Description       : This function clears the RXOVF1 register
*                     
* Parameters        : None
*                     
* Return Value      : None 
*********************************************************************/

void CAN2ClearRXOVF1(void)
{  
   C2RXOVF1 = 0x0000; 
}

#else
#warning "Does not build on this target"
#endif
