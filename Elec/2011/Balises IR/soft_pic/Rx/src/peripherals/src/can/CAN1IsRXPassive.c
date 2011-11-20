#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/***************************************************************************
* Function Name     : CAN1IsRXPassive
* Description       : This function returns the state of CAN receiver whether  
*                     it is in error passive mode.
* Parameters        : None
* Return Value      : char: RXEP bit status
***************************************************************************/

char CAN1IsRXPassive(void)
{
    return C1INTFbits.RXEP;
}

#else
#warning "Does not build on this target"
#endif

#endif

