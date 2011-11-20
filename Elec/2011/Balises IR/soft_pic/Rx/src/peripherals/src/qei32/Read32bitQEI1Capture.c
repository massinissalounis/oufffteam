#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Read32bitQEI1Capture()
* Description       : This function reads capture 
                      register
* Parameters        : None
* Return Value      : 32-bit value of capture register
*********************************************************************/

unsigned long Read32bitQEI1Capture(void)
{
	qeiCounter Temp;

	Temp.f.loWord = QEI1ICL;
	Temp.f.hiWord = QEI1ICH;

	return Temp.l;
}

#else
#warning "Does not build on this target"
#endif
