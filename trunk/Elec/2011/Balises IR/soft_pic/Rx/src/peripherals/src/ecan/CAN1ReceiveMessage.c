#include <ecan.h>

#ifdef _C1TXIF

/*************************************************************************
* Function Name     : CAN1ReceiveMessage
* Description       : This function reads the data from the receive buffer 
*                     into an array.
* Parameters        : unsigned char*: data pointer
*                     unsigned char:  data length 
*                     unsigned char:  pointer to DMA buffer
* Return Value      : void
**************************************************************************/

void CAN1ReceiveMessage (unsigned char * data, unsigned char datalen, 
                         unsigned char *DMAptr)
{
    unsigned char i;
    for (i = 0; i<datalen; i++)
    {
        data[i]  = *(DMAptr + i);
    }
}

#else
#warning "Does not build on this target"
#endif
