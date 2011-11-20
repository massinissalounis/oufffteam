#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : Read32bitQEI2PositionCounter()
* Description       : This function reads position counter 
                      register
* Parameters        : None
* Return Value      : 32-bit value of position counter
*********************************************************************/

unsigned long Read32bitQEI2PositionCounter(void)
{
	qeiCounter Temp;

	Temp.f.loWord = POS2CNTL;
	Temp.f.hiWord = POS2HLD;

	return Temp.l;
}

#else
#warning "Does not build on this target"
#endif
