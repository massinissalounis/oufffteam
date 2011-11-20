#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Read32bitQEI1IndexCounter()
* Description       : This function reads index counter 
                      register
* Parameters        : None
* Return Value      : 32-bit value of index counter
*********************************************************************/

unsigned long Read32bitQEI1IndexCounter(void)
{
	qeiCounter Temp;

	Temp.f.loWord = INDX1CNTL;
	Temp.f.hiWord = INDX1HLD;

	return Temp.l;
}

#else
#warning "Does not build on this target"
#endif
