#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1EnableFilter
* Description       : This function enables the acceptance filter  
*                     
* Parameters        : char: filter_no
*                     
* Return Value      : None 
*********************************************************************/

void CAN1EnableFilter(char filter_no)
{  
    if (filter_no <= 15)
       C1FEN1 |= ((unsigned short)1 << filter_no);
    
}

#else
#warning "Does not build on this target"
#endif
