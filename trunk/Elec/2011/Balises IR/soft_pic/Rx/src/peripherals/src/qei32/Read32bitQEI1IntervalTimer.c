#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Read32bitQEI1IntervalTimer()
* Description       : This function reads interval timer 
                      register
* Parameters        : None
* Return Value      : 32-bit value of interval timer hold register
*********************************************************************/

unsigned long Read32bitQEI1IntervalTimer(void)
{
	qeiCounter Temp;

	Temp.f.loWord = INT1HLDL;
	Temp.f.hiWord = INT1HLDH;

	return Temp.l;
}

#else
#warning "Does not build on this target"
#endif
