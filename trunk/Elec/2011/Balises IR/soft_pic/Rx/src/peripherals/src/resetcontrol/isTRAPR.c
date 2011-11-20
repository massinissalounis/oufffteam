#include <reset.h>

/*********************************************************************
* Function Name     : isSWR
* Description       : Checks if reset is due to Trap Reset.
* Parameters        : None
* Return Value      : Returns 1 if reset is due to TRAPR, else 0
*********************************************************************/

char isTRAPR(void)
{
    char status = 0;
    status = (char)RCONbits.TRAPR;
    /* clear the TRAPR bit so that next read to be meaningful */
    RCONbits.TRAPR = 0;
    return (status); /* return TRAPR bit status */
}
