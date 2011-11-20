#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2GetTXErrorCount
* Description       : This function gets the transmit error count
* Parameters        : None
* Return Value      : unsigned char: transmit error count
*********************************************************************/

unsigned char CAN2GetTXErrorCount(void)
{
    return ((unsigned char) (C2EC >> 8));      /* upper byte of C2EC */
}

#else
#warning "Does not build on this target"
#endif
