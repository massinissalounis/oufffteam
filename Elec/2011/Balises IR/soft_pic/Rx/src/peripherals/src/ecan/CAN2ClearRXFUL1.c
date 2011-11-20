#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2ClearRXFUL1
* Description       : This function clears the RXFUL1 register
*                     
* Parameters        : None
*                     
* Return Value      : None 
*********************************************************************/

void CAN2ClearRXFUL1(void)
{  
   C2RXFUL1 = 0x0000; 
}

#else
#warning "Does not build on this target"
#endif
