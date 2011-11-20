#include <qei.h>

#ifdef _QEI2IF

/*********************************************************************
* Function Name   : WriteQEI2()
* Description     : This function sets the MAX2CNT value.
* Parameters      : unsigned int
* Return Value    : None
*********************************************************************/

void WriteQEI2(unsigned int position)
{
    MAX2CNT = position;  /* set the Maxium Count */
}

#else
#warning "Does not build on this target"
#endif
