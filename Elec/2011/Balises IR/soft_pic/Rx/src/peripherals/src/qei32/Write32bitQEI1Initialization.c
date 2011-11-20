#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Write32bitQEI1Initialization()
* Description       : This function writes to initialization 
                      register
* Parameters        : Pointer to union qeiCounter, which has the
		      value to be written to initialization register
* Return Value      : None
*********************************************************************/

void Write32bitQEI1Initialization(qeiCounter *ptr)
{
	QEI1ICH  = ptr->f.hiWord;
	QEI1ICL  = ptr->f.loWord;
}

#else
#warning "Does not build on this target"
#endif
