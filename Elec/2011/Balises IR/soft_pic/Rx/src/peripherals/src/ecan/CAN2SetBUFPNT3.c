#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2SetBUFPNT3
* Description       : This function sets the ECAN filter 8-11 buffer
*                     pointer register
* Parameters        : unsigned int : pointer_value
* Return Value      : None 
*********************************************************************/

void CAN2SetBUFPNT3(unsigned int pointer_value)
{  
   C2BUFPNT3 = pointer_value; 
}

#else
#warning "Does not build on this target"
#endif

