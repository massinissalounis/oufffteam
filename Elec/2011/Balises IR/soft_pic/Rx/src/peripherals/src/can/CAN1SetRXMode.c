#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/****************************************************************************
* Function Name     : CAN1SetRXMode
* Description       : This function configures the CxRXxCON register
* Parameters        : char buffno, unsigned int config
* Return Value      : None 
*****************************************************************************/

void CAN1SetRXMode(char buffno, unsigned int config)
{  
    switch(buffno)
    {
    case 0:
      C1RX0CON = config;
      break;
    case 1:
      C1RX1CON = config;
      break;
    default:
      C1RX0CON = config;
      break;
    }
}

#else
#warning "Does not build on this target"
#endif

#endif

