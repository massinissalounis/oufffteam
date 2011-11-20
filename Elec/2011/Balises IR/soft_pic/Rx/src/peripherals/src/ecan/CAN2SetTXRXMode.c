#include <ecan.h>

#ifdef _C2TXIF

/****************************************************************************
* Function Name     : CAN2SetTXRXMode
* Description       : This function configures the CxTRmnCON register
* Parameters        : char buffno, unsigned int config
* Return Value      : None 
*****************************************************************************/

void CAN2SetTXRXMode(char buffno, unsigned int config)
{  
    switch(buffno)
    {
    case 0:
    case 1:
      C2TR01CON = config;
      break;
    case 2:
    case 3: 
      C2TR23CON = config;
      break;
    case 4:
    case 5: 
      C2TR45CON = config;
      break;
    case 6:
    case 7: 
      C2TR67CON = config;
      break; 
    }
}

#else
#warning "Does not build on this target"
#endif
