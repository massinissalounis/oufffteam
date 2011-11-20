#include <qei.h>

#ifdef _QEIIF

/*********************************************************************
* Function Name   : WriteQEI()
* Description     : This function sets the MAXCNT value.
* Parameters      : unsigned int
* Return Value    : None
*********************************************************************/

void WriteQEI(unsigned int position)
{
    MAXCNT = position;  /* set the Maxium Count */
}

#else
#warning "Does not build on this target"
#endif
