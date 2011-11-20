#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/****************************************************************************
* Function Name     : CAN1IsTXReady
* Description       : This function returns TXREQ bit status which indicates 
*                     whether the transmitter is ready for next transmission.
* Parameters        : char: buffno
* Return Value      : char: compliment of TXREQ bit status 
*****************************************************************************/

char CAN1IsTXReady(char buffno)
{  
    switch(buffno)
    {
    case 0:
        return !(C1TX0CONbits.TXREQ);
        break;
    case 1:
        return !(C1TX1CONbits.TXREQ);
        break;
    case 2:
        return !(C1TX2CONbits.TXREQ);
        break;
    }
    return 0;
}

#else
#warning "Does not build on this target"
#endif

#endif

