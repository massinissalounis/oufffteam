#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2SetMaskSource
* Description       : This function sets the mask source for filter bits
*                     
* Parameters        : unsigned int : mask_val1, mask_val2
*                     
* Return Value      : None 
*********************************************************************/

void CAN2SetMaskSource (unsigned int mask_val1, unsigned int mask_val2)
{  
      C2FMSKSEL1 = mask_val1;  
      C2FMSKSEL2 = mask_val2;
}

#else
#warning "Does not build on this target"
#endif
