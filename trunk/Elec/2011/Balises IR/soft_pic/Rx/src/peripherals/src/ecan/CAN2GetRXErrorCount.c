#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2GetRXErrorCount
* Description       : This function gets the receive error count
* Parameters        : None
* Return Value      : unsigned char: receive error count
*********************************************************************/

unsigned char CAN2GetRXErrorCount(void)
{
    return ((unsigned char) (C2EC & 0xFF));  /* returns the lower byte of C2EC */
}

#else
#warning "Does not build on this target"
#endif
