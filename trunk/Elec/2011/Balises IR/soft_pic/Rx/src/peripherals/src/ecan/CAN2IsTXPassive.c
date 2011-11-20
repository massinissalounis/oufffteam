#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2IsTXPassive
* Description       : This function returns the state of CAN tranmitter 
*                     whether it is in error passive mode.
* Parameters        : None
* Return Value      : char: TXBP bit status  
*********************************************************************/

char CAN2IsTXPassive(void)
{
    return C2INTFbits.TXBP;
}

#else
#warning "Does not build on this target"
#endif
