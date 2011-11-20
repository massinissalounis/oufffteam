#include <reset.h>

#ifdef _BOR

/*********************************************************************
* Function Name     : isBOR
* Description       : Checks if reset is due to brown-out
* Parameters        : None
* Return Value      : Return 1 if reset is due to BOR , else 0
*********************************************************************/
#define MASK_BOR_AND_POR_BITS 0x3
#define MASK_BOR_FULL_FLEDGED 0x2

char isBOR(void)
{
    char status = 0;
    /* returns 1 if reset is due to BOR full fledged */
    /* when POR, BOR gets set too */
    if((RCON & MASK_BOR_AND_POR_BITS) == MASK_BOR_FULL_FLEDGED) status = 1;
    /* clear the BOR bit so that next read to be meaningful */
    RCONbits.BOR = 0;
    return (status); /* return BOR bit status */

}

#else
#warning "Does not build on this target"
#endif
