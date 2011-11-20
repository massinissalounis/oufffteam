#include <ecan.h>

#ifdef _C1TXIF

/***************************************************************************
* Function Name     : CAN1IsTXPassive
* Description       : This function returns the state of CAN tranmitter 
*                     whether it is in error passive mode.
* Parameters        : None
* Return Value      : char: TXBP bit status  
****************************************************************************/

char CAN1IsTXPassive(void)
{
    return C1INTFbits.TXBP;
}

#else
#warning "Does not build on this target"
#endif
