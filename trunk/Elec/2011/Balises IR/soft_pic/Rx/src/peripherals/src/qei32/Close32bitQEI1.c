#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Close32bitQEI1()
* Description       : This function disabled the QEI1 and its interrupt 
                      bits
* Parameters        : None
* Return Value      : None
*********************************************************************/

void Close32bitQEI1(void)
{
    _QEI1IE = 0;     /* disable interrupt */
    QEI1CONbits.QEIEN = 0x0;    /* QEI/Timer off */  
    _QEI1IF = 0;     /* clear IF flag */
}

#else
#warning "Does not build on this target"
#endif
