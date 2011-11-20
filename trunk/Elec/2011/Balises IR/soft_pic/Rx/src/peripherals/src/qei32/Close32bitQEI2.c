#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : Close32bitQEI2()
* Description       : This function disabled the QEI2 and its interrupt 
                      bits
* Parameters        : None
* Return Value      : None
*********************************************************************/

void Close32bitQEI2(void)
{
    _QEI2IE = 0;     /* disable interrupt */
    QEI2CONbits.QEIEN = 0x0;    /* QEI/Timer off */  
    _QEI2IF = 0;     /* clear IF flag */
}

#else
#warning "Does not build on this target"
#endif
