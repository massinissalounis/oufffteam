#include <ports.h>

#ifdef _INT1IF

/*************************************************************
* Function Name     : CloseINT1
* Description       : Disables external interrupt on pin INT1
* Parameters        : None
* Return Value      : None
**************************************************************/

void CloseINT1(void)
{
    /* Disables external interrupt INT1 */
    _INT1IE = 0;
    _INT1IF = 0;
}
/* end of function CloseINT1 */

#else
#warning "Does not build on this target"
#endif
