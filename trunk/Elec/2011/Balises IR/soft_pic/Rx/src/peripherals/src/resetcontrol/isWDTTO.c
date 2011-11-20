#include <reset.h>

/*******************************************************************
* Function Name     : isWDTTO
* Description       : Checks whether reset condition is due to  
                      WDT time-out.
* Parameters        : None
* Return Value      : returns WDTO bit status
********************************************************************/

char isWDTTO(void)
{
    char status = 0;
    status = (char)RCONbits.WDTO;
    /* clear the WDTO bit so that next read to be meaningful */
    RCONbits.WDTO = 0;
    return (status); /* return EXTR bit status */
}
