#include <outcompare.h>

#ifdef _OC14IF

/************************************************************************
*    Function Name:  ConfigIntOC14                                   	*
*    Description:    This Function Configures Interrupt and sets        *
*                    Interrupt Priority                                 *
*    Parameters:     unsigned int config                                *
*    Return Value:   None                                               *
************************************************************************/

void ConfigIntOC14(unsigned int config)
{
    _OC14IF = 0;                   /* Clear IF bit */
    _OC14IP = (config &0x0007);    /* Assign Interrupt Priority */
    _OC14IE = (config &0x0008)>>3; /* Enable/disable Interrupt */
}

#else
#warning "Does not build on this target"
#endif
