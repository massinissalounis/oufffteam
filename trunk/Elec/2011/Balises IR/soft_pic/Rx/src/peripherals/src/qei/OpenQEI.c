#include <qei.h>

#ifdef _QEIIF

/*********************************************************************
* Function Name     : OpenQEI()
* Description       : This function Clears the CNTERR bit and Configures register 
                      QEICON and DFLTCON for the QEI/Timer functionality.
* Parameters        : unsigned int config1, unsigned int config2
* Return Value      : None
*********************************************************************/

void OpenQEI(unsigned int config1, unsigned int config2)
{
    /* clear CNTERR bit */
    QEICONbits.CNTERR = 0;
	
    /* configures the QEI/Timer */
    QEICON = config1 & 0x2fff;

    QEICONbits.UPDN = config1 >>11; /* assign up/down  */

    /* configures the Digital Filters */
    DFLTCON = config2;
}

#else
#warning "Does not build on this target"
#endif
