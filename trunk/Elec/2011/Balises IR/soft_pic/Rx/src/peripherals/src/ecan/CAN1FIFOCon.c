#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1FIFOCon
* Description       : This function sets the ECAN FIFO control register
*                     
* Parameters        : unsigned int : fifo_val
*                     
* Return Value      : None 
*********************************************************************/

void CAN1FIFOCon(unsigned int fifo_val)
{  
   C1FCTRL = fifo_val; 
}

#else
#warning "Does not build on this target"
#endif
