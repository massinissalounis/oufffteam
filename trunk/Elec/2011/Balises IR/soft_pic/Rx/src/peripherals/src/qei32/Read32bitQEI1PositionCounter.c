#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Read32bitQEI1PositionCounter()
* Description       : This function reads position counter 
                      register
* Parameters        : None
* Return Value      : 32-bit value of position counter
*********************************************************************/

unsigned long Read32bitQEI1PositionCounter(void)
{
	qeiCounter Temp;

	Temp.f.loWord = POS1CNTL;
	Temp.f.hiWord = POS1HLD;

	return Temp.l;
}

#else
#warning "Does not build on this target"
#endif
