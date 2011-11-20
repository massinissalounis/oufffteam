#include <ecan.h>

#ifdef _C2TXIF

/***************************************************************************
* Function Name     : CAN2IsRXPassive
* Description       : This function returns the state of CAN receiver whether
*                     it is in error passive mode.
* Parameters        : None
* Return Value      : char: RXBP bit status 
****************************************************************************/

char CAN2IsRXPassive(void)
{
    return C2INTFbits.RXBP;
}

#else
#warning "Does not build on this target"
#endif
