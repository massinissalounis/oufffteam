#include <outcompare.h>

#ifdef _OC16IF

/************************************************************************
*    Function Name:  ConfigIntOC16                                   	*
*    Description:    This Function Configures Interrupt and sets        *
*                    Interrupt Priority                                 *
*    Parameters:     unsigned int config                                *
*    Return Value:   None                                               *
************************************************************************/

void ConfigIntOC16(unsigned int config)
{
    _OC16IF = 0;                   /* Clear IF bit */
    _OC16IP = (config &0x0007);    /* Assign Interrupt Priority */
    _OC16IE = (config &0x0008)>>3; /* Enable/disable Interrupt */
}

#else
#warning "Does not build on this target"
#endif
