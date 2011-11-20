#include<ports.h>

#ifdef _INT0IF

/**************************************************************
* Function Name     : CloseINT0
* Description       : Disables external interrupt on pin INT0
* Parameters        : None
* Return Value      : None
**************************************************************/

void CloseINT0(void)
{
    /* Disables external interrupt INT0 */
    _INT0IE = 0;
    _INT0IF = 0;
}
/* end of function CloseINT0 */

#else
#warning "Does not build on this target"
#endif
