#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/************************************************************************
* Function Name     : ConfigIntCAN2
* Description       : This function configures the interrupts for CAN2
*
* Parameters        : unsigned int: config1 individual interrupt enable
*                     unsigned int: config2 interrupt priority and 
*                                   enable/disable  information
* Return Value      : None
*************************************************************************/

void ConfigIntCAN2(unsigned int config1, unsigned int config2)
{
    C2INTF = 0;                          /* individual flag register cleared */

    IFS2bits.C2IF = 0;                   /* Clear combined IRQ C2IF */
    C2INTE = config1;            

    IPC9bits.C2IP = config2 & 0x07;      /* set interrupt priority */
    IEC2bits.C2IE = (config2 & 0x08) >>3;/* enable or disable interrupt*/
}

#else
#warning "Does not build on this target"
#endif

#endif

