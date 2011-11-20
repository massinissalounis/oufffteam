#include <ports.h>

#ifdef _INT0IF

/********************************************************************
* Function Name     : ConfigINT0
* Description       : Enables external interrupt on pin INT0.
* Parameters        : config determines the interrupt edge, priority 
*                     and enable/disable information.
* Return Value      : None
********************************************************************/

void ConfigINT0(unsigned int config)
{
    _INT0IF = 0;                       /* clear the interrupt flag */
    _INT0IP = config & 0x07;           /* assign interrupt priority */
    _INT0IE = (config & 0x08) >> 3;    /* enable/disable interrupt */
    _INT0EP = (config & 0x10) >> 4; /* assign edge selected */
  
    #ifdef _GIE
    _GIE = (config & 0x20) >>5;      /* Global interrupt selected*/
    #endif


}
/* end of function ConfigINT0 */

#else
#warning "Does not build on this target"
#endif
