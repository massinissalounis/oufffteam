#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/*********************************************************************
* Function Name     : CAN1GetTXErrorCount
* Description       : This function gets the transmit error count
* Parameters        : None
* Return Value      : unsigned char: transmit error count 
*********************************************************************/

unsigned char CAN1GetTXErrorCount(void)
{
    return C1TERRCNT;    /* upper byte of C1EC */
}

#else
#warning "Does not build on this target"
#endif

#endif

