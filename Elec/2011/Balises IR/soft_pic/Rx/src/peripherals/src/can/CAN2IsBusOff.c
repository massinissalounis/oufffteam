#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/*********************************************************************
* Function Name     : CAN2IsBusOff
* Description       : This function returns the status of the node,
*                     indicating whether CAN is in BusOff error mode.
* Parameters        : None
* Return Value      : char:TXBO bit status 
*********************************************************************/

char CAN2IsBusOff(void)
{
    return C2INTFbits.TXBO;
}

#else
#warning "Does not build on this target"
#endif

#endif

