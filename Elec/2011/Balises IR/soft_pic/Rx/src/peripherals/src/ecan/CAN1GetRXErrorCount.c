#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1GetRXErrorCount
* Description       : This function gets the receive error count
* Parameters        : None
* Return Value      : unsigned char: receive error count
*********************************************************************/

unsigned char CAN1GetRXErrorCount(void)
{
    return ((unsigned char) (C1EC & 0xFF));  /* returns the lower byte of C1EC */
}

#else
#warning "Does not build on this target"
#endif
