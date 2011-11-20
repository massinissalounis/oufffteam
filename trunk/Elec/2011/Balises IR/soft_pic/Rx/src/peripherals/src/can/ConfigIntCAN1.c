#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/************************************************************************
* Function Name     : ConfigIntCAN1
* Description       : This function configures the interrupts for CAN1
*
* Parameters        : unsigned int: config1 individual interrupt enable
*                     unsigned int: config2 interrupt priority and 
*                                   enable/disable information
* Return Value      : None
*************************************************************************/

void ConfigIntCAN1(unsigned int config1, unsigned int config2)
{
    C1INTF = 0;                          /* individual flag register cleared */

    IFS1bits.C1IF = 0;                   /* Clear combined IRQ C2IF */
    C1INTE = config1;

    IPC6bits.C1IP = config2 & 0x07;      /* set interrupt priority */
    IEC1bits.C1IE = (config2 & 0x08) >>3;/* enable or disable interrupt */
}

#else
#warning "Does not build on this target"
#endif

#endif

