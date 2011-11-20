#include <reset.h>

#ifdef _LVDIF

/***********************************************************************
* Function Name     : isLVD
* Description       : Checks if low voltage detect interrupt flag is set
* Parameters        : None
* Return Value      : Return LVDIF bit status
***********************************************************************/

char isLVD(void)
{
    return IFS2bits.LVDIF;      /* returns 1 LVDIF bit is set */
}

#else
#warning "Does not build on this target"
#endif
