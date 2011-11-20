#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/*********************************************************************************
* Function Name     : CAN1SetOperationModeNoWait
* Description       : This function sets the abort bit and configures the 
*                     following bits of CxCTRL: CSIDL, REQOP<2:0> and CANCKS
* Parameters        : unsigned int config
* Return Value      : None 
**********************************************************************************/

void CAN1SetOperationModeNoWait(unsigned int config)
{
   C1CTRLbits.ABAT = 1;
   C1CTRL = config;
}

#else
#warning "Does not build on this target"
#endif

#endif

