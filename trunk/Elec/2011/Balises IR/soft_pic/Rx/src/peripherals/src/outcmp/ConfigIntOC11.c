#include <outcompare.h>

#ifdef _OC11IF

/************************************************************************
*    Function Name:  ConfigIntOC11                                   	*
*    Description:    This Function Configures Interrupt and sets        *
*                    Interrupt Priority                                 *
*    Parameters:     unsigned int config                                *
*    Return Value:   None                                               *
************************************************************************/

void ConfigIntOC11(unsigned int config)
{
    _OC11IF = 0;                   /* Clear IF bit */
    _OC11IP = (config &0x0007);    /* Assign Interrupt Priority */
    _OC11IE = (config &0x0008)>>3; /* Enable/disable Interrupt */
}

#else
#warning "Does not build on this target"
#endif
