#include <outcompare.h>

#ifdef _OC9IF

/************************************************************************
*    Function Name:  ConfigIntOC9                                	    *
*    Description:    This Function Configures Interrupt and sets        *
*                    Interrupt Priority                                 *
*    Parameters:     unsigned int config                                *
*    Return Value:   None                                               *
************************************************************************/

void ConfigIntOC9(unsigned int config)
{
    _OC9IF = 0;                   /* Clear IF bit */
    _OC9IP = (config &0x0007);    /* Assign Interrupt Priority */
    _OC9IE = (config &0x0008)>>3; /* Enable/disable Interrupt */
}

#else
#warning "Does not build on this target"
#endif
