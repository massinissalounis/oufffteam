#include <qei.h>

#ifdef _QEI1IF

/*********************************************************************
* Function Name     : ConfigIntQEI1()
* Description       : This function Configures QEI1 Interrupt and interrupt
*					  priority and clears the interrupt flag.
* Parameters        : unsigned int
* Return Value      : None
*********************************************************************/

void ConfigIntQEI1(unsigned int config)
{
    _QEI1IF = 0;                 /* clear Interrupt flag */
    _QEI1IP = config & 0x07;     /* bits <2:0> is the priority*/
    _QEI1IE = (config & 0x8)>>3; /* bit 3 is interrupt enable/diable */
}

#else
#warning "Does not build on this target"
#endif

