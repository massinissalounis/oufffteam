#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/***************************************************************************
* Function Name     : CAN1IsTXPassive
* Description       : This function returns the state of CAN tranmitter 
*                     whether it is in error passive mode.
* Parameters        : None
* Return Value      : char:TXEP bit status  
****************************************************************************/

char CAN1IsTXPassive(void)
{
    return C1INTFbits.TXEP;
}

#else
#warning "Does not build on this target"
#endif

#endif

