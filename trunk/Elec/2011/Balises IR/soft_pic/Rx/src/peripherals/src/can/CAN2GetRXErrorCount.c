#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/*********************************************************************
* Function Name     : CAN2GetRXErrorCount
* Description       : This function gets the receive error count
* Parameters        : None
* Return Value      : unsigned char:  receive error count
*********************************************************************/

unsigned char CAN2GetRXErrorCount(void)
{
    return C2RERRCNT;/* returns the lower byte of C2EC */
}

#else
#warning "Does not build on this target"
#endif

#endif

