#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2ClearRXOVF2
* Description       : This function clears the RXOVF2 register
*                     
* Parameters        : None
*                     
* Return Value      : None 
*********************************************************************/

void CAN2ClearRXOVF2(void)
{  
   C2RXOVF2 = 0x0000; 
}

#else
#warning "Does not build on this target"
#endif
