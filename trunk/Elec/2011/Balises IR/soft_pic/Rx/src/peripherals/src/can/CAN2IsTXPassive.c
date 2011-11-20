#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/*********************************************************************
* Function Name     : CAN2IsTXPassive
* Description       : This function returns the state of CAN tranmitter 
*                     whether it is in error passive mode.
* Parameters        : None
* Return Value      : char: TXEP bit status  
*********************************************************************/

char CAN2IsTXPassive(void)
{
    return(C2INTFbits.TXEP);
}

#else
#warning "Does not build on this target"
#endif

#endif

