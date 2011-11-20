#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : Read32bitQEI2IntervalTimer()
* Description       : This function reads interval timer 
                      register
* Parameters        : None
* Return Value      : 32-bit value of interval timer hold register
*********************************************************************/

unsigned long Read32bitQEI2IntervalTimer(void)
{
	qeiCounter Temp;

	Temp.f.loWord = INT2HLDL;
	Temp.f.hiWord = INT2HLDH;

	return Temp.l;
}

#else
#warning "Does not build on this target"
#endif
