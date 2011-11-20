#include <qei.h>

#ifdef _QEI1IF

/*********************************************************************
* Function Name   : WriteQEI1()
* Description     : This function sets the MAX1CNT value.
* Parameters      : unsigned int
* Return Value    : None
*********************************************************************/

void WriteQEI1(unsigned int position)
{
    MAX1CNT = position;  /* set the Maxium Count */
}

#else
#warning "Does not build on this target"
#endif
