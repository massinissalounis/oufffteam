#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/****************************************************************************
* Function Name     : CAN2SetRXMode
* Description       : This function configures the following bits of CxRXxCON:
*                     RXRTR, RXM<1:0>,DBEN(if buffer is 0),  
* Parameters        : char buffno, unsigned int config
* Return Value      : None 
*****************************************************************************/

void CAN2SetRXMode(char buffno, unsigned int config)
{  
    switch(buffno)
    {
    case 0:
      C2RX0CON = config;
      break;
    case 1:
      C2RX1CON = config;
      break;
    default:
      C2RX0CON = config;
      break;
    }
}

#else
#warning "Does not build on this target"
#endif

#endif

