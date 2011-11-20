#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/***************************************************************************
* Function Name     : CAN1IsRXReady
* Description       : This function returns RXFUL bit status which indicates 
*                     whether the receive buffer contains any received message
* Parameters        : char buffno
* Return Value      : char: RXFUL bit status
****************************************************************************/

char CAN1IsRXReady(char buffno)
{  
    switch(buffno)
    {
    case 0:
        return C1RX0CONbits.RXFUL;
    case 1:
        return C1RX1CONbits.RXFUL;
    }
    return 0;
}

#else
#warning "Does not build on this target"
#endif

#endif

