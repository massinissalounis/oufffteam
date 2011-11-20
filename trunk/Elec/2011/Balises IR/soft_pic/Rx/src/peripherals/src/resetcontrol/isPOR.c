#include <reset.h>

/*********************************************************************
* Function Name     : isPOR
* Description       : Checks if reset is due to power on.
* Parameters        : None
* Return Value      : Returns 1 if reset is due to POR, else 0
*********************************************************************/

char isPOR(void)
{
    char status = 0;
    /* returns 1 if reset is due to POR */
    if((status = (char)RCONbits.POR)== 1)
    {
        /* clear the POR bit so that next read to be meaningful */
        /* at the same time clear BOR bit (if present) which is set the same time */
        RCONbits.POR = 0;
#ifdef _BOR
        RCONbits.BOR = 0;
#endif
	    }    
    return (status); /* return POR bit status */

    
}
