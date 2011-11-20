#include <ecan.h>

#ifdef _C1TXIF

/***************************************************************************
* Function Name     : CAN1IsRXReady
* Description       : This function returns RXFUL bit status which indicates 
*                     whether the receive buffer contains any received message
* Parameters        : char: buffno
* Return Value      : unsigned short: RXFUL bit status
****************************************************************************/

unsigned short CAN1IsRXReady(char buffno)
{  
    if (buffno <= 15) 
       return C1RXFUL1 & ((unsigned short) 1 << buffno);
    else if (buffno <= 31)
       return C1RXFUL2 & ((unsigned short) 1 << (buffno - 16));
    else 
       return 0;
}

#else
#warning "Does not build on this target"
#endif
