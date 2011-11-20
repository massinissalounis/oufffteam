#include <ecan.h>

#ifdef _C1TXIF

/****************************************************************************
* Function Name     : ECAN1IsTXReady
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
        return !(C1TR01CONbits.TXREQ0);
        break;
    case 1:
        return !(C1TR01CONbits.TXREQ1);
        break;
    case 2:
        return !(C1TR23CONbits.TXREQ2);
        break;
    case 3:
        return !(C1TR23CONbits.TXREQ3);
        break;
    case 4:
        return !(C1TR45CONbits.TXREQ4);
        break;
    case 5:
        return !(C1TR45CONbits.TXREQ5);
        break;
    case 6:
        return !(C1TR67CONbits.TXREQ6);
        break;
    case 7:
        return !(C1TR67CONbits.TXREQ7);
        break;
    default:
        return 0;
        break;
    }
}

#else
#warning "Does not build on this target"
#endif
