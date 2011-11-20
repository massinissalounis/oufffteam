#include <outcompare.h>

#ifdef _OC13IF

/************************************************************************
*    Function Name:  ConfigIntOC13                                   	*
*    Description:    This Function Configures Interrupt and sets        *
*                    Interrupt Priority                                 *
*    Parameters:     unsigned int config                                *
*    Return Value:   None                                               *
************************************************************************/

void ConfigIntOC13(unsigned int config)
{
    _OC13IF = 0;                   /* Clear IF bit */
    _OC13IP = (config &0x0007);    /* Assign Interrupt Priority */
    _OC13IE = (config &0x0008)>>3; /* Enable/disable Interrupt */
}

#else
#warning "Does not build on this target"
#endif
