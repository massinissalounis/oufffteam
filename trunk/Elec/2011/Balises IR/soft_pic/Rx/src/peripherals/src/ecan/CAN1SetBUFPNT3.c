#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1SetBUFPNT3
* Description       : This function sets the ECAN filter 8-11 buffer
*                     pointer register
* Parameters        : unsigned int : pointer_value
* Return Value      : None 
*********************************************************************/

void CAN1SetBUFPNT3(unsigned int pointer_value)
{  
   C1BUFPNT3 = pointer_value; 
   
}

#else
#warning "Does not build on this target"
#endif
