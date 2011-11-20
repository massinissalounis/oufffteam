#include <ecan.h>

#ifdef _C1TXIF

/************************************************************************
* Function Name     : ConfigIntCAN1
* Description       : This function configures the interrupts for CAN1
*
* Parameters        : unsigned int: config1 individual interrupt enable
*                     unsigned char: config2 interrupt priority and 
*                                   enable/disable information
*                                   8..4        3      2..0
*                                   reserved  En/Dis   Prio
* Return Value      : None
*************************************************************************/

void ConfigIntCAN1(unsigned int config1, unsigned char config2)
{
    C1INTF = 0;                   /* individual flag register cleared */

    _C1IF = 0;                    /* Clear combined IRQ C2IF */
    C1INTE = config1;

    _C1IP = config2 & 0x07;       /* set interrupt priority */
    _C1IE = (config2 & 0x08) >>3; /* enable or disable interrupt */
}

#else
#warning "Does not build on this target"
#endif

