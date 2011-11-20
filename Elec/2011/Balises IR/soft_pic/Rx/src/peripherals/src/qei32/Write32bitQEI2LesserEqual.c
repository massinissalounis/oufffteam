#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : Write32bitQEI2LesserEqual()
* Description       : This function writes to lesser than or 
                      equal register
* Parameters        : Pointer to union qeiCounter, which has the
		      value to be written to lesser than or
 		      equal register
* Return Value      : None
*********************************************************************/

void Write32bitQEI2LesserEqual(qeiCounter *ptr)
{
	QEI2LECH  = ptr->f.hiWord;
	QEI2LECL = ptr->f.loWord;
}

#else
#warning "Does not build on this target"
#endif
