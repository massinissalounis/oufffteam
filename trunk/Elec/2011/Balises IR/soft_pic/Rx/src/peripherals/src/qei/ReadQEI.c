#include <qei.h>

#ifdef _QEIIF

/*********************************************************************
* Function Name     : ReadQEI()
* Description       : This function returns the POSCNT register value
* Parameters        : None
* Return Value      : unsigned int
*********************************************************************/

unsigned int ReadQEI(void)
{
    return POSCNT;  /* return the current position count */
}

#else
#warning "Does not build on this target"
#endif
