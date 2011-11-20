#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : Read32bitQEI2VelocityCounter()
* Description       : This function reads velocity counter 
                      register
* Parameters        : None
* Return Value      : 16-bit value of velocity counter
*********************************************************************/

unsigned int Read32bitQEI2VelocityCounter(void)
{
	return VEL2CNT;
}

#else
#warning "Does not build on this target"
#endif
