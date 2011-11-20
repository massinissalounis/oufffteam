#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2SetBUFPNT4
* Description       : This function sets the ECAN filter 12-15 buffer
*                     pointer register
* Parameters        : unsigned int : pointer_value
* Return Value      : None 
*********************************************************************/

void CAN2SetBUFPNT4(unsigned int pointer_value)
{  
   C2BUFPNT4 = pointer_value; 
}

#else
#warning "Does not build on this target"
#endif
