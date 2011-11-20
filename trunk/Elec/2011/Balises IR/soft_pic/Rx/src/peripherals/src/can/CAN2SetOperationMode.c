#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/***************************************************************************
* Function Name     : CAN2SetOperationMode
* Description       : This function configures the following bits of CxCTRL: 
*                     CSIDL, REQOP<2:0> and CANCKS
* Parameters        : unsigned int config
* Return Value      : None 
****************************************************************************/

void CAN2SetOperationMode(unsigned int config)
{
   C2CTRL = config;
}

#else
#warning "Does not build on this target"
#endif

#endif

