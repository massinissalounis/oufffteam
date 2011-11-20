#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : Write32bitQEI2IndexCounter()
* Description       : This function writes to index counter 
                      register
* Parameters        : Pointer to union qeiCounter, which has the
		      value to be written to index counter
* Return Value      : None
*********************************************************************/

void Write32bitQEI2IndexCounter(qeiCounter *ptr)
{
	INDX2HLD  = ptr->f.hiWord;
	INDX2CNTL = ptr->f.loWord;
}

#else
#warning "Does not build on this target"
#endif
