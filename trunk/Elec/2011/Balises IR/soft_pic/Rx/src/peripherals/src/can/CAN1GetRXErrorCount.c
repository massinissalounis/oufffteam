#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/*********************************************************************
* Function Name     : CAN1GetRXErrorCount
* Description       : This function gets the receiver error count
* Parameters        : None
* Return Value      : unsigned char: receiver error count
*********************************************************************/

unsigned char CAN1GetRXErrorCount(void)
{
    return C1RERRCNT;  /* returns the lower byte of C1EC */
}

#else 
#warning "Does not build on this target"
#endif

#endif

