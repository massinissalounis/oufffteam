#include <ports.h>

#ifdef _INT2IF

/**************************************************************
* Function Name     : CloseINT2
* Description       : Disables external interrupt on pin INT2
* Parameters        : None
* Return Value      : None
***************************************************************/

void CloseINT2(void)
{
    /* Disables external interrupt INT2 */
    _INT2IE = 0;
    _INT2IF = 0;
}
/* end of function CloseINT2 */

#else
#warning "Does not build on this target"
#endif
