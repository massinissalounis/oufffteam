#include <reset.h>

/*********************************************************************
* Function Name     : isIOPUWR
* Description       : Checks if reset is due to Illegal OpCode or 
*                     Uninitialized Write Access Reset.
* Parameters        : None
* Return Value      : Returns 1 if reset is due to IOPUWR, else 0
*********************************************************************/

char isIOPUWR(void)
{
    char status = 0;
    status = RCONbits.IOPUWR;
    /* clear the IOPUWR bit so that next read to be meaningful */
    RCONbits.IOPUWR = 0;
    return (status); /* return IOPUWR bit status */
}
