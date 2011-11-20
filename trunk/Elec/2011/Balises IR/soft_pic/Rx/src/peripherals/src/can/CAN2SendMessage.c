#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/******************************************************************************
* Function Name     : CAN2SendMessage
* Description       : This function writes the message identifiers (SID, EID), 
                      writes the data to be transmitted into the Transmit buffer
*                     and sets the corresponding Transmit request bit.
* Parameters        : unsigned long: id
*                     unsigned char: * data
*                     unsigned char: datalen 
*                     char: MsgFlag
* Return Value      : None 
*******************************************************************************/

void CAN2SendMessage(unsigned int sid, unsigned long eid, unsigned char * data, unsigned char  datalen, 
                     char MsgFlag)
{
    int i;
    unsigned int uppereid = eid >> 16;
    switch(MsgFlag)
    {
    case 0:
        C2TX0SID = sid;
        C2TX0EID = uppereid;
        C2TX0DLC = eid;
        break;
    case 1:
        C2TX1SID = sid;
        C2TX1EID = uppereid;
        C2TX1DLC = eid;
        break;
    case 2:
        C2TX2SID = sid;
        C2TX2EID = uppereid;
        C2TX2DLC = eid;
	break;
    default:
        C2TX0SID = sid;
        C2TX0EID = uppereid;
        C2TX0DLC = eid;
        break;
    }
    for(i=0;i < datalen;i++)
    {
        switch(MsgFlag)
        {
        case 0: *((unsigned char *)&C2TX0B1+i)= data[i];
            break;
        case 1: *((unsigned char *)&C2TX1B1+i)= data[i];
            break;
        case 2: *((unsigned char *)&C2TX2B1+i)= data[i];
            break;
        default:*((unsigned char *)&C2TX0B1+i)= data[i];
            break;
        }
    }
    /* Msg send request*/
    switch(MsgFlag)
    {
    case 0:
        C2TX0DLCbits.DLC = datalen;
        C2TX0CONbits.TXREQ = 1;
        break;
    case 1:
        C2TX1DLCbits.DLC = datalen;
        C2TX1CONbits.TXREQ = 1;
        break;
    case 2:
        C2TX2DLCbits.DLC = datalen;
        C2TX2CONbits.TXREQ = 1;
        break;
    default:
        C2TX0DLCbits.DLC = datalen;
        C2TX0CONbits.TXREQ = 1;
        break;
    }
}

#else
#warning "Does not build on this target"
#endif

#endif

