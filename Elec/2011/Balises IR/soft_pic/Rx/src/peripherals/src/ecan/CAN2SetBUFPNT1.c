#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2SetBUFPNT1
* Description       : This function sets the ECAN filter 0-3 buffer
*                     pointer register
* Parameters        : unsigned int : pointer_value
* Return Value      : None 
*********************************************************************/

void CAN2SetBUFPNT1(unsigned int pointer_value)
{  
   C2BUFPNT1 = pointer_value; 
}

#else
#warning "Does not build on this target"
#endif

