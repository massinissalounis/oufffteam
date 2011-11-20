#include <qei.h>

#ifdef _QEIIF

/**************************************************************************
* Function Name     : CloseQEI()
* Description       : This routine disables the QEI and its interrupt bits. 
* Parameters        : None
* Return Value      : None
***************************************************************************/

void CloseQEI(void)
{
    _QEIIE = 0;     /* disable interrupt */
    _QEIM = 0x0;    /* QEI/Timer off */  
    _QEIIF = 0;     /* clear IF flag */
}

#else
#warning "Does not build on this target"
#endif
