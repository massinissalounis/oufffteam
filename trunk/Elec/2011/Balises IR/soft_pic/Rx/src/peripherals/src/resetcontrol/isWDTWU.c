#include <reset.h>

/********************************************************************
* Function Name     : isWDTWU
* Description       : Checks if wake up from SLEEP is due to WDT 
* Parameters        : None
* Return Value      : Return WDTO bit status if wakeup from sleep
********************************************************************/
#define MASK_WDTO_AND_SLEEP_BITS 0x0018

char isWDTWU(void)
{
    char status = 0;
    if((RCON & MASK_WDTO_AND_SLEEP_BITS) == MASK_WDTO_AND_SLEEP_BITS)
    {
        status = 1;
        /* clear both SLEEP and WDTO bits */
        RCONbits.WDTO = 0;
        RCONbits.SLEEP = 0;
    }
    
    /* return 1 if device wake up is due to WDT timeout */
    return status;
}
