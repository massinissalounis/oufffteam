#include <reset.h>

/*********************************************************************
* Function Name     : isCM
* Description       : Checks if reset is due to Config Mismatched
* Parameters        : None
* Return Value      : Returns 1 if reset is due to CM, else 0
*********************************************************************/
#ifdef _CM

char isCM(void)
{
    char status = 0;
    status = (char)RCONbits.CM;
    /* clear the CM bit so that next read to be meaningful */
    RCONbits.CM = 0;
    return (status); /* return CM bit status */
}

#endif
