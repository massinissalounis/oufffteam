#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Write32bitQEI1IntervalTimer()
* Description       : This function writes to Interval Timer 
                      register
* Parameters        : Pointer to union qeiCounter, which has the
		      value to be written to interval timer
* Return Value      : None
*********************************************************************/

void Write32bitQEI1IntervalTimer(qeiCounter *ptr)
{
	INT1TMRH  = ptr->f.hiWord;
	INT1TMRL = ptr->f.loWord;
}

#else
#warning "Does not build on this target"
#endif
