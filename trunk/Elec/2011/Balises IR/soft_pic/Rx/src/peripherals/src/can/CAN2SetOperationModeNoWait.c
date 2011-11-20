#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/*********************************************************************************
* Function Name     : CAN2SetOperationModeNoWait
* Description       : This function sets the abort bit and configures the 
                      following bits of CxCTRL: CSIDL, REQOP<2:0> and CANCKS
* Parameters        : unsigned int config
* Return Value      : None 
**********************************************************************************/

void CAN2SetOperationModeNoWait(unsigned int config)
{
   C2CTRLbits.ABAT = 1;
   C2CTRL = config;
}

#else
#warning "Does not build on this target"
#endif

#endif

