#include <ports.h>

#ifdef _INT4IF

/************************************************************
* Function Name     : CloseINT4
* Description       : Disables external interrupt on pin INT4
* Parameters        : None
* Return Value      : None
************************************************************/

void CloseINT4(void)
{
    /* Disables external interrupt INT4 */
    _INT4IE = 0;
    _INT4IF = 0;
}

#else
#warning "Does not build on this target"
#endif
