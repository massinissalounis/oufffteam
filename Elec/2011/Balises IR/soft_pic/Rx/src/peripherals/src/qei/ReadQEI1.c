#include <qei.h>

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : ReadQEI1()
* Description       : This function returns the POS1CNT register value
* Parameters        : None
* Return Value      : unsigned int
*********************************************************************/

unsigned int ReadQEI1(void)
{
    return POS1CNT;  /* return the current position count */
}

#else
#warning "Does not build on this target"
#endif
