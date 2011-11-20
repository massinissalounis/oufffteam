#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Write32bitQEI1PositionCounter()
* Description       : This function writes to position counter 
                      register
* Parameters        : Pointer to union qeiCounter, which has the
		      value to be written to position counter
* Return Value      : None
*********************************************************************/

void Write32bitQEI1PositionCounter(qeiCounter *ptr)
{
	POS1HLD  = ptr->f.hiWord;
	POS1CNTL = ptr->f.loWord;
}

#else
#warning "Does not build on this target"
#endif
