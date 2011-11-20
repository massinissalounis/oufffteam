#include <qei.h>

#ifdef _QEI1IF

/**************************************************************************
* Function Name     : CloseQEI1()
* Description       : This routine disables the QEI1 and its interrupt bits. 
* Parameters        : None
* Return Value      : None
***************************************************************************/

void CloseQEI1(void)
{
    _QEI1IE = 0;     /* disable interrupt */
    QEI1CONbits.QEIM = 0x0;    /* QEI/Timer off */  
    _QEI1IF = 0;     /* clear IF flag */
}

#else
#warning "Does not build on this target"
#endif
