#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1SetBUFPNT2
* Description       : This function sets the ECAN filter 4-7 buffer
*                     pointer register
* Parameters        : unsigned int : pointer_value
* Return Value      : None 
*********************************************************************/

void CAN1SetBUFPNT2(unsigned int pointer_value)
{  
   C1BUFPNT2 = pointer_value; 
}

#else
#warning "Does not build on this target"
#endif
