#include "qei32.h"

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : ConfigInt32bitQEI1()
* Description       : This function Configures QEI1 Interrupt and interrupt
*		      priority and clears the interrupt flag.
* Parameters        : unsigned int config
* Return Value      : None
*********************************************************************/

void ConfigInt32bitQEI1(unsigned int config)
{
    _QEI1IF = 0;                 	   /* clear Interrupt flag */
    _QEI1IP = (config & 0x0007);     /* set priority */
    _QEI1IE = (config & 0x0008)>> 3; 	   /* interrupt enable/diable */
}

#else
#warning "Does not build on this target"
#endif

