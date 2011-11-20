#include <reset.h>

/*********************************************************************
* Function Name     : isMCLR
* Description       : Checks if reset condition is due to MCLR low
* Parameters        : None
* Return Value      : Return EXTR bit status
*********************************************************************/

char isMCLR(void)
{
    char status = 0;
    status = (char)RCONbits.EXTR;
    /* clear the EXTR bit so that next read to be meaningful */
    RCONbits.EXTR = 0;
    return (status); /* return EXTR bit status */
}
