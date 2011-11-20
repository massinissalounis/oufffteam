#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/*********************************************************************
* Function Name     : CAN2GetTXErrorCount
* Description       : This function gets the transmit error count
* Parameters        : None
* Return Value      : unsigned char: transmit error count
*********************************************************************/

unsigned char CAN2GetTXErrorCount(void)
{
    return C2TERRCNT;      /* upper byte of C2EC */
}

#else
#warning "Does not build on this target"
#endif

#endif

