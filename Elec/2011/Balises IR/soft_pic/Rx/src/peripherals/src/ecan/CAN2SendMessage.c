#include <ecan.h>

#ifdef _C2TXIF

/******************************************************************************
* Function Name     : CAN2SendMessage
* Description       : This function writes the message identifiers (SID & EID), 
                      writes the data to be transmitted into the Transmit buffer
*                     and sets the corresponding Transmit request bit.
* Parameters        : unsigned char: 	*data
*                     unsigned char: 	datalen
*                     unsigned long:	txIdentifier (Send 29 bit identifier < SID<10:0> : EID<17:0> > in case of Extended Message)
													 (Send 11 bit identifier < SID<10:0> > in case of Standard Message) 	
*                     unsigned char: 	ide
*                     unsigned char: 	remoteTransmit
*		   			  unsigned int:		*dmaBaseAddress
* 		      		  unsigned char:	MsgFlag
* Return Value      : None 
*******************************************************************************/

void CAN2SendMessage(unsigned char *data, unsigned char datalen, unsigned long txIdentifier,\
unsigned char ide, unsigned char remoteTransmit, unsigned int *dmaBaseAddress, unsigned char MsgFlag){
   
unsigned char i;
unsigned int word1;
unsigned int word2, word0;
char *ptr;

switch(ide)
	{

case 0: 
    // Standard ID
	word0 = (unsigned short)(((txIdentifier & 0x7FF) << 2) | 0);
	word2 = (unsigned short)((remoteTransmit << 9) | (1 << 4) | datalen);
	break;

case 1:
	//Extended ID
	word0 = (unsigned short)((((txIdentifier>>18) & 0x7FF) << 2) | (1 << 1) | 1);
	word1 = (unsigned short)((txIdentifier>>6) & 0xFFF);
	word2 = (unsigned short)(((txIdentifier & 0x3F) << 10) | (remoteTransmit << 9) | 
	                          ( 1 << 8) | (1 << 4) | datalen);
	break;

default:

	word0 = (unsigned short)((((txIdentifier>>18) & 0x7FF) << 2) | 0);
	word2 = (unsigned short)((remoteTransmit << 9) | (1 << 4) | datalen);
	break;

	}


// Obtain the Address of Transmit Buffer in DMA RAM for a given Transmit Buffer number
	dmaBaseAddress[0] = word0;
	dmaBaseAddress[1] = word1;
	dmaBaseAddress[2] = word2;
   
	ptr=(char *)&dmaBaseAddress[3];
	for(i = 0;i < datalen;i++)
	    {

		*ptr++ = data[i];
	
	    }


    /* Msg send request */
    switch(MsgFlag)
    {
    case 0:
        C2TR01CONbits.TXREQ0 = 1;
        break;
    case 1:
        C2TR01CONbits.TXREQ1 = 1;
        break;
    case 2:
        C2TR23CONbits.TXREQ2 = 1;
        break;
    case 3:
        C2TR23CONbits.TXREQ3 = 1;
        break;
    case 4:
        C2TR45CONbits.TXREQ4 = 1;
        break;
    case 5:
        C2TR45CONbits.TXREQ5 = 1;
        break;
    case 6:
        C2TR67CONbits.TXREQ6 = 1;
        break;
    case 7:
        C2TR67CONbits.TXREQ7 = 1;
        break;
    default:
        C2TR01CONbits.TXREQ0 = 1;
        break;
    }
}

#else
#warning "Does not build on this target"
#endif


