#include <ecan.h>

#ifdef _C2TXIF

/***************************************************************************
* Function Name     : CAN2SetOperationMode
* Description       : This function configures the following bits of CxCTRL1: 
*                     CSIDL, REQOP<2:0> and CANCKS and DNCNT<4:0> of CxCTRL2
* Parameters        : unsigned int config1, unsigned int config2
* Return Value      : None 
****************************************************************************/

void CAN2SetOperationMode(unsigned int config1, unsigned int config2)
{
   C2CTRL1 = config1;
   C2CTRL2 = config2;
}

#else
#warning "Does not build on this target"
#endif
