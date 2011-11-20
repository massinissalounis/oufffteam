#include <outcompare.h>

#ifdef _OC15IF

/************************************************************************
*    Function Name:  ConfigIntOC15                                   	*
*    Description:    This Function Configures Interrupt and sets        *
*                    Interrupt Priority                                 *
*    Parameters:     unsigned int config                                *
*    Return Value:   None                                               *
************************************************************************/

void ConfigIntOC15(unsigned int config)
{
    _OC15IF = 0;                   /* Clear IF bit */
    _OC15IP = (config &0x0007);    /* Assign Interrupt Priority */
    _OC15IE = (config &0x0008)>>3; /* Enable/disable Interrupt */
}

#else
#warning "Does not build on this target"
#endif
