#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/****************************************************************************
* Function Name     : CAN2SetTXMode
* Description       : This function configures the following bits of CxTXxCON:
*                     TXRTR, TXREQ, TXPRI<1:0>  
* Parameters        : char buffno, unsigned int config
* Return Value      : None 
*****************************************************************************/

void CAN2SetTXMode(char buffno, unsigned int config)
{  
    switch(buffno)
    {
    case 0:
      C2TX0CON = config;
      break;
    case 1:
      C2TX1CON = config;
      break;
    case 2:
      C2TX2CON = config;
      break;
    default:
      C2TX0CON = config;
      break;
    }
}

#else
#warning "Does not build on this target"
#endif

#endif

