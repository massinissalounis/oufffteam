#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : Write32bitQEI2GreaterEqual()
* Description       : This function writes to greater than or 
                      equal register
* Parameters        : Pointer to union qeiCounter, which has the
		      value to be written to greater than or
 		      equal register
* Return Value      : None
*********************************************************************/

void Write32bitQEI2GreaterEqual(qeiCounter *ptr)
{
	QEI2GECH  = ptr->f.hiWord;
	QEI2GECL = ptr->f.loWord;
}

#else
#warning "Does not build on this target"
#endif
