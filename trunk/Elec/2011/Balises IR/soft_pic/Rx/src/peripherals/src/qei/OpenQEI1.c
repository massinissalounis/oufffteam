#include <qei.h>

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : OpenQEI1()
* Description       : This function Clears the CNTERR bit and Configures register 
                      QEICON and DFLTCON for the QEI/Timer functionality.
* Parameters        : unsigned int config1, unsigned int config2
* Return Value      : None
*********************************************************************/

void OpenQEI1(unsigned int config1, unsigned int config2)
{
    /* clear CNTERR bit */
    QEI1CONbits.CNTERR = 0;
	
    /* configures the QEI/Timer */
    QEI1CON = config1 & 0x2fff;

    QEI1CONbits.UPDN = config1 >>11; /* assign up/down  */

    /* configures the Digital Filters */
    DFLT1CON = config2;
}

#else
#warning "Does not build on this target"
#endif
