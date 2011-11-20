#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2EnableFilter
* Description       : This function enables the acceptance filter  
* Parameters        : char: filter_no
* Return Value      : None 
*********************************************************************/

void CAN2EnableFilter(char filter_no)
{  
    
    if (filter_no <= 15)
      C2FEN1 |= ((unsigned short)1 << filter_no);
}

#else
#warning "Does not build on this target"
#endif
