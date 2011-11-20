#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/****************************************************************************
* Function Name     : CAN2IsRXReady
* Description       : This function returns RXFUL bit status which indicates 
*                     whether the receive buffer contains any received message
* Parameters        : char: buffno
* Return Value      : char:RXFUL bit status 
*****************************************************************************/

char CAN2IsRXReady(char buffno)
{  
    switch(buffno)
    {
    case 0:
        return(C2RX0CONbits.RXFUL);
    case 1:
        return(C2RX1CONbits.RXFUL);
    }
    return 0;
}

#else
#warning "Does not build on this target"
#endif

#endif

