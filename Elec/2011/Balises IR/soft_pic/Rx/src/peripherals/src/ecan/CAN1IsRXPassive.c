#include <ecan.h>

#ifdef _C1TXIF

/***************************************************************************
* Function Name     : CAN1IsRXPassive
* Description       : This function returns the state of CAN receiver whether  
*                     it is in error passive mode.
* Parameters        : None
* Return Value      : char: RXBP bit status
***************************************************************************/

char CAN1IsRXPassive(void)
{
    return C1INTFbits.RXBP;
}

#else
#warning "Does not build on this target"
#endif
