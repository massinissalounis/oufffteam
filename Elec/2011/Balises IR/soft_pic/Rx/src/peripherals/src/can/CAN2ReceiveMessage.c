#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/*************************************************************************
* Function Name     : CAN2ReceiveMessage
* Description       : This function reads the data from the receive buffer 
*                     into an array.
* Parameters        : unsigned char*: data pointer
*                     unsigned char:  datalen 
*                     char:           MsgFlag
* Return Value      : void
**************************************************************************/

void CAN2ReceiveMessage(unsigned char * data, unsigned char  datalen, 
                        char MsgFlag)
{
	int i;
    for(i = 0;i<datalen;i++)
    {
        switch(MsgFlag)
        {
        case 0:
            data[i]  = *((unsigned char *)&C2RX0B1 + i);
            break;
        case 1: 
            data[i]  = *((unsigned char *)&C2RX1B1 + i);
            break;
        default: 
            data[i]  = *((unsigned char *)&C2RX0B1 + i);
            break;
        }
    }
}

#else
#warning "Does not build on this target"
#endif

#endif

