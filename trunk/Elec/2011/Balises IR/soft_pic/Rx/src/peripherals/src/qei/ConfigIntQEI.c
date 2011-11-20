#include <qei.h>

#ifdef _QEIIF

/*********************************************************************
* Function Name     : ConfigIntQEI()
* Description       : This function Configures QEI Interrupt and interrupt
*					  priority and clears the interrupt flag.
* Parameters        : unsigned int
* Return Value      : None
*********************************************************************/

void ConfigIntQEI(unsigned int config)
{
    _QEIIF = 0;                 /* clear Interrupt flag */
    _QEIIP = config & 0x07;     /* bits <2:0> is the priority*/
    _QEIIE = (config & 0x8)>>3; /* bit 3 is interrupt enable/diable */
}

#else
#warning "Does not build on this target"
#endif

