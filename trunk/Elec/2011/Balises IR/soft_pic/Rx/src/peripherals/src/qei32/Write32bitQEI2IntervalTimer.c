#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : Write32bitQEI2IntervalTimer()
* Description       : This function writes to Interval Timer 
                      register
* Parameters        : Pointer to union qeiCounter, which has the
		      value to be written to interval timer
* Return Value      : None
*********************************************************************/

void Write32bitQEI2IntervalTimer(qeiCounter *ptr)
{
	INT2TMRH  = ptr->f.hiWord;
	INT2TMRL = ptr->f.loWord;
}

#else
#warning "Does not build on this target"
#endif
