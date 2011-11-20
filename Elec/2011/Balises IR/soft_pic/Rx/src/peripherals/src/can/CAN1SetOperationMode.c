#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/***************************************************************************
* Function Name     : CAN1SetOperationMode
* Description       : This function configures the following bits of CxCTRL: 
*                     CSIDL, REQOP<2:0> and CANCKS
* Parameters        : unsigned int config
* Return Value      : None 
****************************************************************************/

void CAN1SetOperationMode(unsigned int config)
{
   C1CTRL = config;
}

#else
#warning "Does not build on this target"
#endif

#endif

