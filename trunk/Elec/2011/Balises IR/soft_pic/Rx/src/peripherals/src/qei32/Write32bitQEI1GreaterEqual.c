#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Write32bitQEI1GreaterEqual()
* Description       : This function writes to greater than or 
                      equal register
* Parameters        : Pointer to union qeiCounter, which has the
		      value to be written to greater than or
 		      equal register
* Return Value      : None
*********************************************************************/

void Write32bitQEI1GreaterEqual(qeiCounter *ptr)
{
	QEI1GECH  = ptr->f.hiWord;
	QEI1GECL = ptr->f.loWord;
}

#else
#warning "Does not build on this target"
#endif
