#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/***************************************************************************
* Function Name     : CAN2IsTXReady
* Description       : This function returns TXREQ bit status which indicates 
*                     whether the transmitter is ready for next transmission.
* Parameters        : char: buffno
* Return Value      : char: compliment of TXREQ bit status 
****************************************************************************/

char CAN2IsTXReady(char buffno)
{  
    switch(buffno)
    {
    case 0:
        return !(C2TX0CONbits.TXREQ);
        break;
    case 1:
        return !(C2TX1CONbits.TXREQ);
        break;
    case 2:
        return !(C2TX2CONbits.TXREQ);
        break;
    }
    return 0;
}

#else
#warning "Does not build on this target"
#endif

#endif

