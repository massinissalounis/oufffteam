#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : Read32bitQEI2Capture()
* Description       : This function reads capture 
                      register
* Parameters        : None
* Return Value      : 32-bit value of capture register
*********************************************************************/

unsigned long Read32bitQEI2Capture(void)
{
	qeiCounter Temp;

	Temp.f.loWord = QEI2ICL;
	Temp.f.hiWord = QEI2ICH;

	return Temp.l;
}

#else
#warning "Does not build on this target"
#endif
