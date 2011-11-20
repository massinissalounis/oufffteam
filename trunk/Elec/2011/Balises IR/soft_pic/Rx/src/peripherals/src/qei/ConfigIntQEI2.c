#include <qei.h>

#ifdef _QEI2IF

/*********************************************************************
* Function Name     : ConfigIntQEI2()
* Description       : This function Configures QEI2 Interrupt and interrupt
*					  priority and clears the interrupt flag.
* Parameters        : unsigned int
* Return Value      : None
*********************************************************************/

void ConfigIntQEI2(unsigned int config)
{
    _QEI2IF = 0;                 /* clear Interrupt flag */
    _QEI2IP = config & 0x07;     /* bits <2:0> is the priority*/
    _QEI2IE = (config & 0x8)>>3; /* bit 3 is interrupt enable/diable */
}

#else
#warning "Does not build on this target"
#endif

