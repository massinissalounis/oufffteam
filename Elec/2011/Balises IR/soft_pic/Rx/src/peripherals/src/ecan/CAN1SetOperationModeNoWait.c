#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************************
* Function Name     : CAN1SetOperationModeNoWait
* Description       : This function sets the abort bit and configures the 
                      following bits of CxCTRL: CSIDL, REQOP<2:0> and CANCKS
                      and DNCNT<4:0> of CxCTRL2
* Parameters        : unsigned int config1, unsigned int config2 
* Return Value      : None 
**********************************************************************************/

void CAN1SetOperationModeNoWait(unsigned int config1, unsigned int config2)
{
   C1CTRL1bits.ABAT = 1;
   C1CTRL1 = config1;
   C1CTRL2 = config2;
}

#else
#warning "Does not build on this target"
#endif
