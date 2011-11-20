#include <outcompare.h>

#ifdef _OC12IF

/************************************************************************
*    Function Name:  ConfigIntOC12                                   	*
*    Description:    This Function Configures Interrupt and sets        *
*                    Interrupt Priority                                 *
*    Parameters:     unsigned int config                                *
*    Return Value:   None                                               *
************************************************************************/

void ConfigIntOC12(unsigned int config)
{
    _OC12IF = 0;                   /* Clear IF bit */
    _OC12IP = (config &0x0007);    /* Assign Interrupt Priority */
    _OC12IE = (config &0x0008)>>3; /* Enable/disable Interrupt */
}

#else
#warning "Does not build on this target"
#endif
