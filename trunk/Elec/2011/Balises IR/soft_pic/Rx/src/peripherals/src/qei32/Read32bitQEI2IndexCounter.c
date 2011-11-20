#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : Read32bitQEI2IndexCounter()
* Description       : This function reads index counter 
                      register
* Parameters        : None
* Return Value      : 32-bit value of index counter
*********************************************************************/

unsigned long Read32bitQEI2IndexCounter(void)
{
	qeiCounter Temp;

	Temp.f.loWord = INDX2CNTL;
	Temp.f.hiWord = INDX2HLD;

	return Temp.l;
}

#else
#warning "Does not build on this target"
#endif
