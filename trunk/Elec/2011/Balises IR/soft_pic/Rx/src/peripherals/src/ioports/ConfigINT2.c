#include <ports.h>

#ifdef _INT2IF

/*******************************************************************
* Function Name     : ConfigINT2
* Description       : Enables external interrupt on pin INT2.
* Parameters        : config determines the interrupt edge, priority 
*                     and enable/disable information.
* Return Value      : None
********************************************************************/

void ConfigINT2(unsigned int config)
{
    _INT2IF = 0;                       /* clear the interrupt flag */
    _INT2IP = config & 0x07;                   /* assign interrupt priority */
    _INT2IE = (config & 0x08) >> 3;    /* enable/disable interrupt */
    _INT2EP = (config & 0x10) >> 4; /* assign edge selected */

    #ifdef _GIE
    _GIE = (config & 0x20) >>5;      /* Global interrupt selected*/
    #endif

}
/* end of function ConfigINT2 */

#else
#warning "Does not build on this target"
#endif

