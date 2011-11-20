#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1SetMaskSource
* Description       : This function sets the mask source for filter bits
*                     
* Parameters        : unsigned int : mask_val1, mask_val2
*                     
* Return Value      : None 
*********************************************************************/

void CAN1SetMaskSource (unsigned int mask_val1, unsigned int mask_val2)
{  
      C1FMSKSEL1 = mask_val1; 
      C1FMSKSEL2 = mask_val2;
}

#else
#warning "Does not build on this target"
#endif
