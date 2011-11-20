#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/****************************************************************************
* Function Name     : CAN1SetTXMode
* Description       : This function configures the CxTXxCON register
* Parameters        : char buffno, unsigned int config
* Return Value      : None 
*****************************************************************************/

void CAN1SetTXMode(char buffno, unsigned int config)
{  
    switch(buffno)
    {
    case 0:
      C1TX0CON = config;
      break;
    case 1:
      C1TX1CON = config;
      break;
    case 2:
      C1TX2CON = config;
      break;
    default:
      C1TX0CON = config;
      break;
    }
}

#else
#warning "Does not build on this target"
#endif

#endif

