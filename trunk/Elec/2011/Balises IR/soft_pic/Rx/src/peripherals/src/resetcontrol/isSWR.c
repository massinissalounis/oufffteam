#include <reset.h>

/*********************************************************************
* Function Name     : isSWR
* Description       : Checks if reset is due to Software Reset.
* Parameters        : None
* Return Value      : Returns 1 if reset is due to SWR, else 0
*********************************************************************/

char isSWR(void)
{
    char status = 0;
    status = (char)RCONbits.SWR;
    /* clear the SWR bit so that next read to be meaningful */
    RCONbits.SWR = 0;
    return (status); /* return SWR bit status */
}
