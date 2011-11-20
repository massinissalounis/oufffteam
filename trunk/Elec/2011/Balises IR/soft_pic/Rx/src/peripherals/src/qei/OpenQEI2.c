#include <qei.h>

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : OpenQEI2()
* Description       : This function Clears the CNTERR bit and Configures register 
                      QEICON and DFLTCON for the QEI/Timer functionality.
* Parameters        : unsigned int config1, unsigned int config2
* Return Value      : None
*********************************************************************/

void OpenQEI2(unsigned int config1, unsigned int config2)
{
    /* clear CNTERR bit */
    QEI2CONbits.CNTERR = 0;
	
    /* configures the QEI/Timer */
    QEI2CON = config1 & 0x2fff;

    QEI2CONbits.UPDN = config1 >>11; /* assign up/down  */

    /* configures the Digital Filters */
    DFLT2CON = config2;
}

#else
#warning "Does not build on this target"
#endif
