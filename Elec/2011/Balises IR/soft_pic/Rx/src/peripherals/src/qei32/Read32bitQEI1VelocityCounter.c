#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Read32bitQEI1VelocityCounter()
* Description       : This function reads velocity counter 
                      register
* Parameters        : None
* Return Value      : 16-bit value of velocity counter
*********************************************************************/

unsigned int Read32bitQEI1VelocityCounter(void)
{
	return VEL1CNT;
}

#else
#warning "Does not build on this target"
#endif
