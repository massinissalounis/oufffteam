#include <ecan.h>

#ifdef _C1TXIF

/****************************************************************************
* Function Name     : CAN1SetTXRXMode
* Description       : This function configures the CxTRmnCON register
* Parameters        : char buffno, unsigned int config
* Return Value      : None 
*****************************************************************************/

void CAN1SetTXRXMode(char buffno, unsigned int config)
{  
    switch(buffno)
    {
    case 0:
    case 1:
      C1TR01CON = config;
      break;
    case 2:
    case 3: 
      C1TR23CON = config;
      break;
    case 4:
    case 5: 
      C1TR45CON = config;
      break;
    case 6:
    case 7: 
      C1TR67CON = config;
      break; 
    }
}

#else
#warning "Does not build on this target"
#endif
