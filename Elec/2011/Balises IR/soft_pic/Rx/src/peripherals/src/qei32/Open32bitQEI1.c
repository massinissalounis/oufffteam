#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : Open32bitQEI1()
* Description       : This function Configures register 
                      QEICON, QEIIOC and QEISTAT
* Parameters        : unsigned int config1, unsigned int config2
		      unsigned int config3
* Return Value      : None
*********************************************************************/

void Open32bitQEI1(unsigned int config1, unsigned int config2, unsigned int config3)
{
    /* configures the QEI/Timer */
    QEI1CON = config1;


    /* configure QEIIOC register */
    QEI1IOC = config2;

    /* configures the QEISTAT register */
    QEI1STAT = config3;
}

#else
#warning "Does not build on this target"
#endif
