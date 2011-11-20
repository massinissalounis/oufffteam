#include <ports.h>

#ifdef _INT3IF

/**************************************************************************
* Function Name     : CloseINT3
* Description       : Disables external interrupt on pin INT3
* Parameters        : None
* Return Value      : None
*************************************************************************/

void CloseINT3(void)
{
    /* Disables external interrupt INT3 */
    _INT3IE = 0;
    _INT3IF =0;
}

#else
#warning "Does not build on this target"
#endif
