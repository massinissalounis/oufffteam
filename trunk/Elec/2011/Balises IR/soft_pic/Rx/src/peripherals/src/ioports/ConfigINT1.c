#include<ports.h>

#ifdef _INT1IF

/********************************************************************
* Function Name     : ConfigINT1
* Description       : Enables external interrupt on pin INT1.
* Parameters        : config determines the interrupt edge, priority 
*                     and enable/disable information.
* Return Value      : None
********************************************************************/

void ConfigINT1(unsigned int config)
{
    _INT1IF = 0;                       /* clear the interrupt flag */
    _INT1IP = config & 0x07;                   /* assign interrupt priority */
    _INT1IE = (config & 0x08) >> 3;    /* enable/disable interrupt */
    _INT1EP = (config & 0x10) >> 4; /* assign edge selected */

    #ifdef _GIE
    _GIE = (config & 0x20) >>5;      /* Global interrupt selected*/
    #endif

}
/* end of function ConfigINT1 */

#else
#warning "Does not build on this target"
#endif
