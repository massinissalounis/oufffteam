#include <qei.h>

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : ReadQEI2()
* Description       : This function returns the POS2CNT register value
* Parameters        : None
* Return Value      : unsigned int
*********************************************************************/

unsigned int ReadQEI2(void)
{
    return POS2CNT;  /* return the current position count */
}

#else
#warning "Does not build on this target"
#endif
