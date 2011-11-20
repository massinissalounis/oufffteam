#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2ClearRXFUL2
* Description       : This function clears the RXFUL2 register
*                     
* Parameters        : None
*                     
* Return Value      : None 
*********************************************************************/

void CAN2ClearRXFUL2(void)
{  
   C2RXFUL2 = 0x0000; 
}

#else
#warning "Does not build on this target"
#endif
