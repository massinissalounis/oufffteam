#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Write32bitQEI1LesserEqual()
* Description       : This function writes to lesser than or 
                      equal register
* Parameters        : Pointer to union qeiCounter, which has the
		      value to be written to lesser than or
 		      equal register
* Return Value      : None
*********************************************************************/

void Write32bitQEI1LesserEqual(qeiCounter *ptr)
{
	QEI1LECH  = ptr->f.hiWord;
	QEI1LECL = ptr->f.loWord;
}

#else
#warning "Does not build on this target"
#endif
