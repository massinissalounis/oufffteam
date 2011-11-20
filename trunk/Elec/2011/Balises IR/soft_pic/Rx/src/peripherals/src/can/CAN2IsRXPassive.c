#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/***************************************************************************
* Function Name     : CAN2IsRXPassive
* Description       : This function returns the state of CAN receiver whether
*                     it is in error passive mode.
* Parameters        : None
* Return Value      : char: RXEP bit status 
****************************************************************************/

char CAN2IsRXPassive(void)
{
    return (C2INTFbits.RXEP);
}

#else
#warning "Does not build on this target"
#endif

#endif

