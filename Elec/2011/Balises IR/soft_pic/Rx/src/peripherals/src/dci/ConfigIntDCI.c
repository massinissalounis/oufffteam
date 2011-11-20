#include "dci.h"

#ifdef _DCIIF

/**************************************************************************
*    Function Name  : ConfigIntDCI
*    Description    : This Function Configures DCI Interrupt and sets  
*                     Interrupt Priority
*    Parameters     : unsigned int:config
*    Return Value   : None
***************************************************************************/

void ConfigIntDCI(unsigned int config)
{
     _DCIIF = 0;                      /* Clear IF bit */
     _DCIIP = (config & 0x0007);     /* Assign Interrupt Priority */ 
     _DCIIE = (config & 0x0008)>>3;   /* Enable/disable Interrupt */ 
}

#else
#warning "Does not build on this target"
#endif
