#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1GetTXErrorCount
* Description       : This function gets the transmit error count
* Parameters        : None
* Return Value      : unsigned char: transmit error count 
*********************************************************************/

unsigned char CAN1GetTXErrorCount(void)
{
    return ((unsigned char) (C1EC >> 8));    /* upper byte of C1EC */
}

#else
#warning "Does not build on this target"
#endif
