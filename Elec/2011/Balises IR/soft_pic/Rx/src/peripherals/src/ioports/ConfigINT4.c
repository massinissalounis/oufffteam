#include <ports.h>

#ifdef _INT4IF

/*******************************************************************
* Function Name     : ConfigINT4
* Description       : Enables external interrupt on pin INT4.
* Parameters        : config determines the interrupt edge, priority 
*                     and enable/disable information.
* Parameters        : config determines falling or rising edge selection
* Return Value      : None
*********************************************************************/

void ConfigINT4(unsigned int config)
{
    _INT4IF = 0;                               /* clear the interrupt flag */
    _INT4IP = config & 0x07;                   /* assign interrupt priority */
    _INT4IE = (config & 0x08) >> 3;            /* enable/disable interrupt */
    _INT4EP = (config & 0x10) >> 4; /* assign edge selected */

    #ifdef _GIE
    _GIE = (config & 0x20) >>5;      /* Global interrupt selected*/
    #endif

}

#else
#warning "Does not build on this target"
#endif
