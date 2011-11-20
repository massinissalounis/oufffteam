#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Write32bitQEI1IndexCounter()
* Description       : This function writes to index counter 
                      register
* Parameters        : Pointer to union qeiCounter, which has the
		      value to be written to index counter
* Return Value      : None
*********************************************************************/

void Write32bitQEI1IndexCounter(qeiCounter *ptr)
{
	INDX1HLD  = ptr->f.hiWord;
	INDX1CNTL = ptr->f.loWord;
}

#else
#warning "Does not build on this target"
#endif
