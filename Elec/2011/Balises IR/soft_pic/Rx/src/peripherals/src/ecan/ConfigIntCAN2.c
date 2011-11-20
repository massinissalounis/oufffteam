#include <ecan.h>

#ifdef _C2TXIF

/************************************************************************
* Function Name     : ConfigIntCAN2
* Description       : This function configures the interrupts for CAN2
*
* Parameters        : unsigned int: config1 individual interrupt enable
*                     unsigned char: config2 interrupt priority and 
*                                   enable/disable information
*                                   8..4        3      2..0
*                                   reserved  En/Dis   Prio
* Return Value      : None
*************************************************************************/

void ConfigIntCAN2(unsigned int config1, unsigned char config2)
{
    C2INTF = 0;                   /* individual flag register cleared */

    _C2IF = 0;                    /* Clear combined IRQ C2IF */
    C2INTE = config1;            

    _C2IP = config2 & 0x07;       /* set interrupt priority */
    _C2IE = (config2 & 0x08) >>3; /* enable or disable interrupt*/
}

#else
#warning "Does not build on this target"
#endif
