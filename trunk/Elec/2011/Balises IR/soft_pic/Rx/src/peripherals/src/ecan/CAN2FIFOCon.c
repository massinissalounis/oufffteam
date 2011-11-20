#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2FIFOCon
* Description       : This function sets the ECAN FIFO control register
*                     
* Parameters        : unsigned int : fifo_val
*                     
* Return Value      : None 
*********************************************************************/

void CAN2FIFOCon(unsigned int fifo_val)
{  
   C2FCTRL = fifo_val; 
}

#else
#warning "Does not build on this target"
#endif
