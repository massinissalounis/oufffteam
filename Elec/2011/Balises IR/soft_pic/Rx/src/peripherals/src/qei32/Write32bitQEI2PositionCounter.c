#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : Write32bitQEI2PositionCounter()
* Description       : This function writes to position counter 
                      register
* Parameters        : Pointer to union qeiCounter, which has the
		      value to be written to position counter
* Return Value      : None
*********************************************************************/

void Write32bitQEI2PositionCounter(qeiCounter *ptr)
{
	POS2HLD  = ptr->f.hiWord;
	POS2CNTL = ptr->f.loWord;
}

#else
#warning "Does not build on this target"
#endif
