#include <qei.h>

#ifdef _QEI2IF

/**************************************************************************
* Function Name     : CloseQEI2()
* Description       : This routine disables the QEI2 and its interrupt bits. 
* Parameters        : None
* Return Value      : None
***************************************************************************/

void CloseQEI2(void)
{
    _QEI2IE = 0;     /* disable interrupt */
    QEI2CONbits.QEIM = 0x0;    /* QEI/Timer off */  
    _QEI2IF = 0;     /* clear IF flag */
}

#else
#warning "Does not build on this target"
#endif
