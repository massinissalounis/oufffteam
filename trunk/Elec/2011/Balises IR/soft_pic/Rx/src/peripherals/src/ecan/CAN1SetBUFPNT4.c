#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1SetBUFPNT4
* Description       : This function sets the ECAN filter 12-15 buffer
*                     pointer register
* Parameters        : unsigned int : pointer_value
* Return Value      : None 
*********************************************************************/

void CAN1SetBUFPNT4(unsigned int pointer_value)
{  
   C1BUFPNT4 = pointer_value; 
}

#else
#warning "Does not build on this target"
#endif
