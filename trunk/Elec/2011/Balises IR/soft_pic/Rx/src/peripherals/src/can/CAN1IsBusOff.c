#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/*********************************************************************
* Function Name     : CAN1IsBusOff
* Description       : This function returns the status of the node,
*                     indicating whether CAN is in BusOff error mode.
* Parameters        : None
* Return Value      : char:TXBO bit status
*********************************************************************/

char CAN1IsBusOff(void)
{
    return C1INTFbits.TXBO;
}

#else
#warning "Does not build on this target"
#endif

#endif

