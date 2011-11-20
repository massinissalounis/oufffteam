#include "qei32.h"

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : ConfigInt32bitQEI2()
* Description       : This function Configures QEI1 Interrupt and interrupt
*		      priority and clears the interrupt flag.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigInt32bitQEI2(unsigned int config)
{
    _QEI2IF = 0;                 	   /* clear Interrupt flag */
    _QEI2IP = (config & 0x0007);     /* set priority */
    _QEI2IE = (config & 0x0008)>> 3; 	   /* interrupt enable/diable */
}

#else
#warning "Does not build on this target"
#endif

