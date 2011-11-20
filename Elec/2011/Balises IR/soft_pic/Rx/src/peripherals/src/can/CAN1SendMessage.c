#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/******************************************************************************
* Function Name     : CAN1SendMessage
* Description       : This function writes the message identifiers (SID, EID), 
                      writes the data to be transmitted into the Transmit buffer
*                     and sets the corresponding Transmit request bit.
* Parameters        : unsigned long: id
*                     unsigned char: * data
*                     unsigned char: datalen 
*                     char: MsgFlag
* Return Value      : None 
*******************************************************************************/

void CAN1SendMessage(unsigned int sid, unsigned long eid, unsigned char * data, unsigned char  datalen, 
                     char MsgFlag)
{
    int i;
    unsigned int uppereid = eid >> 16;
    switch(MsgFlag)
    {
    case 0:
        C1TX0SID = sid;
        C1TX0EID = uppereid;
        C1TX0DLC = eid;
        break;
    case 1:
        C1TX1SID = sid;
        C1TX1EID = uppereid;
        C1TX1DLC = eid;
        break;
    case 2:
        C1TX2SID = sid;
        C1TX2EID = uppereid;
        C1TX2DLC = eid;
	break;
    default:
        C1TX0SID = sid;
        C1TX0EID = uppereid;
        C1TX0DLC = eid;
        break;
    }
    for(i = 0;i < datalen;i++)
    {
        switch(MsgFlag)
        {
        case 0: *((unsigned char *)&C1TX0B1+i)= data[i];
            break;
        case 1: *((unsigned char *)&C1TX1B1+i)= data[i];
            break;
        case 2: *((unsigned char *)&C1TX2B1+i)= data[i];
            break;
        default:*((unsigned char *)&C1TX0B1+i)= data[i];
            break;
        }
    }

    /* Msg send request */
    switch(MsgFlag)
    {
    case 0:
        C1TX0DLCbits.DLC = datalen;
        C1TX0CONbits.TXREQ = 1;
        break;
    case 1:
        C1TX1DLCbits.DLC = datalen;
        C1TX1CONbits.TXREQ = 1;
        break;
    case 2:
        C1TX2DLCbits.DLC = datalen;
        C1TX2CONbits.TXREQ = 1;
        break;
    default:
        C1TX0DLCbits.DLC = datalen;
        C1TX0CONbits.TXREQ = 1;
        break;
    }
}

#else
#warning "Does not build on this target"
#endif

#endif

